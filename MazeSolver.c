// File: MazeSolver.c
//
// Description:  Implementation of the MazeSolver module. A queue is used to
//               maintain the order that the search is performed. 
// 
// Author:  Ryan Current rjc7379
//
#define _DEFAULT_SOURCE
#define MAX_LINE 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include"MazeQueue.h"

/// maze_node_s is a struct that represents the current Maze. 
/// maze is a 2D array of shorts that represents the current maze
/// queue is a MazeQueue that represents the current queue. 
struct maze_s
{
    char ** maze; 
    MazeQueue queue; 
    size_t r_allocation; 
    unsigned short maxC; 
    unsigned short maxR; 
};

typedef struct maze_s * Maze; 
#define _MAZE_IMPL_
#include "MazeSolver.h"

#define MAZE_INITIAL_ROWS 2


/// Destroys the Maze and free's any memory that was allocated for the maze
void Destroy_Maze(Maze maze)
{
    que_destroy(maze->queue); 
    for(int i = 0; i < maze->maxR; i++)
        free(maze->maze[i]); 
    free(maze->maze); 
    free(maze); 
}


/// gets the current neighbors and adds them to the MazeQueue within the maze
/// that is passed in
/// @param maze the maze that is being solved. 
/// @param node the node to get the neighbors of
void add_neighbors(Maze maze, MazeNode node)
{
    // north
    if(node->currentR > 0)
        if( (maze->maze[node->currentR - 1][node->currentC] == '.') && 
            (!que_has_or_had(maze->queue, node->currentR - 1, node->currentC)) )
        {
            MazeNode neighbor = que_create_node(node->currentR - 1, node->currentC, 
                                                node->currentR, node->currentC); 
            que_insert(maze->queue, neighbor); 
        }

    // south
    if(node->currentR < maze->maxR - 1)
        if((maze->maze[node->currentR + 1][node->currentC] == '.') &&
           (!que_has_or_had(maze->queue, node->currentR + 1, node->currentC)) )
        {
            MazeNode neighbor = que_create_node(node->currentR + 1, node->currentC, 
                                                node->currentR, node->currentC); 
            que_insert(maze->queue, neighbor); 
        }

    // west
    if(node->currentC > 0)
        if((maze->maze[node->currentR][node->currentC - 1] == '.') &&
           (!que_has_or_had(maze->queue, node->currentR, node->currentC - 1)) )
        {
            MazeNode neighbor = que_create_node(node->currentR, node->currentC - 1, 
                                                node->currentR, node->currentC); 
            que_insert(maze->queue, neighbor); 
        }

    // east
    if(node->currentC < maze->maxC - 1)
        if((maze->maze[node->currentR][node->currentC + 1] == '.') &&
           (!que_has_or_had(maze->queue, node->currentR, node->currentC + 1)) )
        {
            MazeNode neighbor = que_create_node(node->currentR, node->currentC + 1, 
                                                node->currentR, node->currentC); 
            que_insert(maze->queue, neighbor); 
        }


}


/// Solves the maze and stores the solution in the Maze object that gets passed
/// in 
void Solve_Maze(Maze maze, FILE * file)
{
    // initialize neighbors list
    if(maze->maxC > 0 && maze->maxR > 0)
    {
        MazeNode neighbor = que_create_node(0, 0, -1, -1); 
            que_insert(maze->queue, neighbor); 
    }
    else
    {
        fprintf(file, "Maze is empty"); 
        return;
    }

    // bfs
    bool solved = false; 
    MazeNode cNode; 
    while(!que_empty(maze->queue))
    {
        cNode = que_next(maze->queue);
        if(cNode->currentR == maze->maxR - 1 && cNode->currentC == maze->maxC - 1)
        {
            solved = true; 
            break; 
        }
        add_neighbors(maze, cNode); 
    }

    if(solved)
    {
        // change path to + and count moves
        int moves = 0; 
        while(cNode->currentR != 0 || cNode->currentC != 0)
        {
            moves++; 
            maze->maze[cNode->currentR][cNode->currentC] = '+'; 
            cNode = que_find(maze->queue, cNode->previousR, cNode->previousC);
            if(cNode == NULL) 
            {
                maze->maze[0][0] = '+'; 
                break; 
            }
        }

        fprintf(file, "Solution in %d steps\n", moves); 
    }
    else
    {
        fprintf(file, "No solution.\n"); 
    }

    
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
            fprintf(file, "%c ", maze->maze[i][j]); 
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
                maze->maze[maze->maxR][j] = '.';
                j++;  
            }
            if(buf[i] == '1')  
            {
                maze->maze[maze->maxR][j] = '#';
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
    new->queue = que_create(); 
    new->maxR = 0; 
    new->maxC = 0; 
    load_maze(new, file); 
    return new;  
}

