// File: MazeSolver.c
//
// Description:  Implementation of the MazeSolver module. A queue is used to
//               maintain the order that the search is performed. 
// 
// Author:  Ryan Current rjc7379
//
#define _DEFAULT_SOURCE
#define MAX_LINE 15
#define FROM_NORTH 'n'
#define FROM_SOUTH 's'
#define FROM_EAST 'e'
#define FROM_WEST 'w'
#define PATH '.'
#define SOLUTION_PATH '+'
#define BOUNDARY '#'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include "QueueADT.h"

/// maze_node_s is a struct that represents the current Maze. 
/// maze is a 2D array of shorts that represents the current maze
/// queue is a MazeQueue that represents the current queue. 
struct maze_s
{
    char ** maze; 
    QueueADT queue; 
    size_t r_allocation; 
    unsigned short maxC; 
    unsigned short maxR; 
};

/// maze_node_s is a struct that represents a node on the graph.
/// R represents the current row
/// C represents the current column 
struct maze_node_s
{
    unsigned short R; 
    unsigned short C; 
}; 

typedef struct maze_node_s * MazeNode; 

typedef struct maze_s * Maze; 
#define _MAZE_IMPL_
#include "MazeSolver.h"

#define MAZE_INITIAL_ROWS 2


/// Destroys the Maze and free's any memory that was allocated for the maze
void Destroy_Maze(Maze maze)
{
    if(maze)
    {
        que_destroy(maze->queue); 
        for(int i = 0; i < maze->maxR; i++)
            free(maze->maze[i]); 
        free(maze->maze); 
        free(maze); 
    }
}


/// gets the current neighbors and adds them to the MazeQueue within the maze
/// that is passed in
/// @param maze the maze that is being solved. 
/// @param node the node to get the neighbors of
void add_neighbors(Maze maze, MazeNode node)
{
    // north
    if(node->R > 0)
    {
        if(maze->maze[node->R - 1][node->C] == PATH)
        {
            MazeNode neighbor = (MazeNode)malloc(sizeof(struct maze_node_s)); 
            neighbor->R = node->R - 1; 
            neighbor->C = node->C; 
            que_insert(maze->queue, neighbor); 
            maze->maze[node->R - 1][node->C] = FROM_SOUTH; 
        }
    }
    
    // south
    if(node->R < maze->maxR - 1)
    {
        if(maze->maze[node->R + 1][node->C] == PATH)
        {
            MazeNode neighbor = (MazeNode)malloc(sizeof(struct maze_node_s)); 
            neighbor->R = node->R + 1; 
            neighbor->C = node->C; 
            que_insert(maze->queue, neighbor); 
            maze->maze[node->R + 1][node->C] = FROM_NORTH;  
        }
    }
    
    // west
    if(node->C > 0)
    {
        if(maze->maze[node->R][node->C - 1] == PATH)
        {
            MazeNode neighbor = (MazeNode)malloc(sizeof(struct maze_node_s)); 
            neighbor->R = node->R; 
            neighbor->C = node->C - 1; 
            que_insert(maze->queue, neighbor); 
            maze->maze[node->R][node->C - 1] = FROM_EAST; 
        }
    }
    
    // east
    if(node->C < maze->maxC - 1)
    {
        if(maze->maze[node->R][node->C + 1] == PATH)
        {
            MazeNode neighbor = (MazeNode)malloc(sizeof(struct maze_node_s)); 
            neighbor->R = node->R; 
            neighbor->C = node->C + 1; 
            que_insert(maze->queue, neighbor); 
            maze->maze[node->R][node->C + 1] = FROM_WEST;                               
        }
    }

}


/// Solves the maze and stores the solution in the Maze object that gets passed
/// in 
int Solve_Maze(Maze maze)
{
    // initialize neighbors list
    if((maze->maxC > 0 || maze->maxR > 0) && maze->maze[0][0] == PATH)
    {
        MazeNode neighbor = (MazeNode)malloc(sizeof(struct maze_node_s)); 
        neighbor->R = 0; 
        neighbor->C = 0; 
        que_insert(maze->queue, neighbor); 
    }
    else
    {
        return -1;
    }
    // bfs
    bool solved = false; 
    MazeNode cNode; // = (MazeNode)malloc(sizeof(struct maze_node_s)); 
    while(!que_empty(maze->queue))
    {
        cNode = (MazeNode)que_remove(maze->queue);
        if(cNode->R == maze->maxR - 1 && cNode->C == maze->maxC - 1)
        {
            solved = true; 
            break; 
        }
        add_neighbors(maze, cNode); 
        free(cNode); 
    }

    int moves = -1; 
    if(solved)
    {
        // change path to + and count moves
        moves = 1; 
        while(cNode->R != 0 || cNode->C != 0)
        {
            moves++; 
            char current = maze->maze[cNode->R][cNode->C]; 
            maze->maze[cNode->R][cNode->C] = SOLUTION_PATH; 
            if(current == FROM_NORTH)
                cNode->R = cNode->R - 1; 
            if(current == FROM_SOUTH)
                cNode->R = cNode->R + 1; 
            if(current == FROM_EAST)
                cNode->C = cNode->C + 1; 
            if(current == FROM_WEST)
                cNode->C = cNode->C - 1; 
            
            if(cNode->R == 0 && cNode->C == 0) 
                break; 
        }
        maze->maze[0][0] = SOLUTION_PATH; 
    }

    free(cNode); 
    while (!que_empty(maze->queue))
    {
        free(que_remove(maze->queue)); 
    }
    // returns -1 if not solved 
    return moves; 
}


/// Prints the maze to stdout with a border and easier to see characters. 
void Pretty_Print_Maze(Maze maze, FILE * file)
{
    // top border
    fprintf(file, "|-"); 
    for(int i = 0; i < maze->maxC; i++)
        fprintf(file, "--"); 
    fprintf(file, "|\n"); 

    // actual maze with left and right border
    for(int i = 0; i < maze->maxR; i++)
    {
        if(i != 0) fprintf(file, "| "); 
        else fprintf(file, "  "); 
        for(int j = 0; j < maze->maxC; j++)
        {
            if(maze->maze[i][j] == PATH ||
               maze->maze[i][j] == SOLUTION_PATH ||
               maze->maze[i][j] == BOUNDARY)
                fprintf(file, "%c ", maze->maze[i][j]); 
            else 
                fprintf(file, "%c ", PATH); 
        }
        if(i != maze->maxR-1) fprintf(file, "|\n"); 
        else fprintf(file, " \n"); 
    }

    //bottom border
    fprintf(file, "|-"); 
    for(int i = 0; i < maze->maxC; i++)
        fprintf(file, "--"); 
    fprintf(file, "|\n"); 

}


/// doubles the number of possible rows that the maze contains 
/// @param maze the maze to increase size 
void realloc_Maze(Maze maze)
{
    char ** temp = (char **)realloc(maze->maze, 2 * maze->r_allocation * sizeof(char **)); 
    maze->r_allocation = 2 * maze->r_allocation;
    maze->maze = temp; 
    assert(maze->maze && "Reallocation of memory failed"); 
}


/// loads the current file into the maze within the maze struct
/// @param maze the maze to load the file into
/// @param file the file to load
void load_maze(Maze maze, FILE * file)
{
    // Initialize values for parsing 
    char* buf = (char*) malloc( sizeof( char) * MAX_LINE);
    size_t n=MAX_LINE;
    ssize_t num;
    
    num = getline( &buf, &n, file); 
    //get the total size of the line 
    if(num > 0)
    {
        for(ssize_t i = 0; i < num; i++)
        {
            if(buf[i] == '0' || buf[i] == '1') maze->maxC++; 
        }
    }

    // read in lines 
    while(num > 0)
    {
        if(maze->r_allocation-1 == maze->maxR)
        {
            realloc_Maze(maze); 
        }

        maze->maze[maze->maxR] = (char *)malloc(maze->maxC * sizeof(char *)); 

        int j = 0; 
        for(ssize_t i = 0; i < num; i++)
        {
            if(buf[i] == '0')
            {
                maze->maze[maze->maxR][j] = PATH;
                j++;  
            }
            if(buf[i] == '1')  
            {
                maze->maze[maze->maxR][j] = BOUNDARY;
                j++;  
            }
        }
        maze->maxR++; 
        num = getline(&buf, &n, file);  
    }
    free(buf); 
}


/// Allocates memory for a Maze and parses the file into a data Type that can
/// be used to solve the maze. 
Maze Create_Maze(FILE * file)
{
    Maze new = (Maze)malloc(sizeof(struct maze_s));
    new->maze = (char **)malloc(MAZE_INITIAL_ROWS * sizeof(char *)); 
    new->r_allocation = MAZE_INITIAL_ROWS; 
    new->maxR = 0; 
    new->maxC = 0; 
    load_maze(new, file); 
    new->queue = que_create(); 
    return new;  
}

