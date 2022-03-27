// File: mopsolver.c
//
// Description:  Uses MazeSolver to load, parse, solve, and print a maze. 
//
// File requirements:
// The file should contain 0's and 1's that represent the maze
// A 0 represents a passable area in the maze 
// A 1 represents a non passable area in the maze
// The file should have the same number of 0's and 1's in every row
// 
// Author:  Ryan Current rjc7379
//

#include"MazeSolver.h"
#include<stdio.h>

int main()
{
    FILE * fp= fopen("./examples/rand0", "r"); 
    Maze maze = Create_Maze(fp); 
    Pretty_Print_Maze(maze); 
    Destroy_Maze(maze); 
    fclose(fp); 
}