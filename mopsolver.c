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

#include "MazeSolver.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>


/// prints out the usage message
void printUsage()
{
    printf("Usage:\n"
            "mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n"
            "Options:\n"
            "   -h          Print usage and options list to stdout only.    (Default: off)\n"
            "   -d          Pretty-print (display) the maze after reading.  (Default: off)\n"
            "   -s          Print length of shortest path or 'No solution'. (Default: off)\n"
            "   -p          Pretty-print maze with the path, if one exists. (Default: off)\n"
            "   -i infile   Read maze from infile.                          (Default: stdin)\n"
            "   -o outfile  Write all output to outfile.                    (Default: stdout)\n"); 
}



/// processes command line arguments, initializes, and solves the maze
/// @param argc  the number of command line arguments
/// @param argv  command line arguments
/// @return EXIT_SUCCESS if success, 1 + EXIT_FAILURE if failure
int main( int argc, char * argv[] )
{
    FILE * inFile = stdin; 
    FILE * outFile = stdout; 
    bool printInitial = false; 
    bool printSteps = false; 
    bool printOptimal = false; 

    int opt;
    while ( (opt = getopt( argc, argv, "hdspi:o:") ) != -1 ) 
    {
        switch ( opt ) 
        {
            case 'h':
                printUsage();
                return EXIT_SUCCESS;
                break;
            case 'd':
                printInitial = true; 
                break; 
            case 's':
                printSteps = true; 
                break; 
            case 'p':
                printOptimal = true; 
                break; 
            case 'i':
                // check that the file exists and can be opened
                if(!(inFile = fopen(optarg, "r")))
                {
                    fprintf(stderr, "INVALID INPUT FILE\n"); 
                    return EXIT_FAILURE;  
                }
                break; 
            case 'o':
                outFile = fopen(optarg, "w"); 
                break; 
        }
    }        
    Maze maze = Create_Maze(inFile);
    if(printInitial) 
        Pretty_Print_Maze(maze, outFile);
    if(printSteps)
    {
        int steps = Solve_Maze(maze); 
        if(steps == -1)
            fprintf(outFile, "No solution.\n"); 
        else    
            fprintf(outFile, "Solution in %d steps.\n", steps); 
    }
    if(printOptimal)
        Pretty_Print_Maze(maze, outFile); 
    Destroy_Maze(maze); 
    fclose(inFile);
    fclose(outFile); 
    return EXIT_SUCCESS;  
}
