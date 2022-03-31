// File: MazeSolver.h
//
// Description:  Interface to the MazeSolver module
//
// Author:  Ryan Current rjc7379
//

#ifndef _MAZESOLVER_H_
#define _MAZESOLVER_H_
#include <stdio.h>
#ifndef _MAZE_IMPL_

/// Maze is a struct that contains information about the maze that is currently 
/// being solved. 
typedef struct maze_s * Maze; 

#endif


/// Allocates memory for a Maze and parses the file into a data Type that can
/// be used to solve the maze. 
/// The file should contain 0's and 1's only, with a 0 representing a path and 
/// a 1 representing a barrier. Numbers should be single spaced, all lines 
/// should be the same length, and the maze should start in the top left and 
/// end in the bottom right. 
/// @param file the file to read and parse the maze from
/// @return Maze pointer that can be passed to other functions to solve the maze
Maze Create_Maze(FILE * file); 


/// Destroys the Maze and free's any memory that was allocated for the maze
/// @param maze the maze to destory
void Destroy_Maze(Maze maze); 


/// Solves the maze and stores the solution in the Maze object that gets passed
/// in 
/// @param maze maze to solve 
int Solve_Maze(Maze maze); 


/// Prints the maze to stdout with a border and easier to see characters. 
/// @param maze maze to pretty print
/// @param file file to print to 
void Pretty_Print_Maze(Maze maze, FILE * file); 




#endif




