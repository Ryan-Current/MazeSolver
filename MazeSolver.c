// File: MazeSolver.c
//
// Description:  Implementation of the MazeSolver module. A queue is used to
//               maintain the order that the search is performed. 
// 
// Author:  Ryan Current rjc7379
//

#include"MazeQueue.h"

/// maze_node_s is a struct that represents the current Maze. 
/// maze is a 2D array of shorts that represents the current maze
/// queue is a MazeQueue that represents the current queue. 
struct maze_s
{
    char ** maze; 
    MazeQueue queue; 
    unsigned short maxC; 
    unsigned short maxR; 
};

typedef struct maze_s * Maze; 
#define _MAZE_IMPL_
#include "MazeSolver.h"

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAZE_INITIAL_ROWS 2


/// determines wheather the current node is at the solution
/// @param maze the maze that the node exists in
/// @param node the node to check 
bool Node_Is_Solution(Maze maze, MazeNode node)
{
    return ((maze->maxC == node->currentC) && (maze->maxR == node->currentR)); 
}


/// Destroys the Maze and free's any memory that was allocated for the maze
void Destroy_Maze(Maze maze)
{
    if(maze->maxC != -1)
        printf("IMPLEMENT DESTROY MAZE FUNTION\n"); 
}



/// Solves the maze and stores the solution in the Maze object that gets passed
/// in 
void Solve_Maze(Maze maze)
{
    if(maze->maxC != -1)
        printf("IMPLEMENT SOLVE FUNCTION \n"); 

}


/// Prints the maze to stdout with a border and easier to see characters. 
void Pretty_Print_Maze(Maze maze)
{
    // top border
    printf("|-"); 
    for(int i = 0; i < maze->maxC; i++)
        printf("--"); 
    printf("|\n"); 

    // actual maze with left and right border
    for(int i = 0; i < maze->maxR; i++)
    {
        if(i != 0) printf("| "); 
        else printf("  "); 
        for(int j = 0; j < maze->maxC; j++)
        {
            printf("%c ", maze->maze[i][j]); 
        }
        if(i != maze->maxR-1) printf("|\n"); 
        else printf(" \n"); 
    }

    //bottom border
    printf("|-"); 
    for(int i = 0; i < maze->maxC; i++)
        printf("--"); 
    printf("|\n"); 

}


/// checks if the node has already been enqueued or checked. 
/// @param maze the maze that is being solved. 
/// @param node the node to check
bool maze_node_checked(Maze maze, MazeNode node)
{
    if(maze->maxC != -1)
        if(node->currentC != -1)
            printf("IMPLEMENT MAZE NODE CHECKED FUNCTION\n"); 
    return false; 
}


/// gets the current neighbors and adds them to the MazeQueue within the maze
/// that is passed in
/// @param maze the maze that is being solved. 
/// @param node the node to get the neighbors of
void get_neighbors(Maze maze, MazeNode node)
{
    if(maze->maxC != -1)
        if(node->currentC != -1)
            printf("IMPLEMENT GET NEIGHBORS\n"); 

}


/// doubles the number of possible rows that the maze contains 
/// @param maze the maze to increase size 
void realloc_Maze(Maze maze)
{
    char ** temp = (char **)realloc(maze->maze, 2 * sizeof(maze->maze)); 
    maze->maze = temp; 
    assert(maze->maze && "Reallocation of memory failed"); 
}


/// loads the current file into the maze within the maze struct
/// @param maze the maze to load the file into
/// @param file the file to load
void load_maze(Maze maze, FILE * file)
{
    // Initialize values for parsing 
    char * buffer = NULL;
    size_t bufferSize = 0;
    ssize_t line_size;

    // get the size of each row 
    line_size = getline(&buffer, &bufferSize, file);
    if(line_size > 0)
    {
        for(ssize_t i = 0; i < line_size; i++)
        {
            if(buffer[i] == '0' || buffer[i] == '1') maze->maxC++; 
        }
    }

    // read in lines 
    while(line_size > 0)
    {
        if(sizeof(* maze->maze)/sizeof(char **) == maze->maxR)
        {
            realloc_Maze(maze); 
        }

        maze->maze[maze->maxR] = (char *)malloc(maze->maxC * sizeof(char *)); 

        int j = 0; 
        for(ssize_t i = 0; i < line_size; i++)
        {
            if(buffer[i] == '0')
            {
                maze->maze[maze->maxR][j] = '.';
                j++;  
            }
            if(buffer[i] == '1')  
            {
                maze->maze[maze->maxR][j] = '#';
                j++;  
            }
        }
        maze->maxR++; 
        line_size = getline(&buffer, &bufferSize, file);  
    }
    
}


/// Allocates memory for a Maze and parses the file into a data Type that can
/// be used to solve the maze. 
Maze Create_Maze(FILE * file)
{
    Maze new = (Maze)malloc(sizeof(struct maze_s));
    new->maze = (char **)malloc(MAZE_INITIAL_ROWS * sizeof(short*)); 
    new->queue = que_create(); 
    load_maze(new, file); 
    return new;  
}

