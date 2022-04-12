// File: MazeQueue.h
//
// Description:  Interface to the MazeQueue module
//
// Author:  Ryan Current rjc7379
//

#ifndef _MazeQueue_H_
#define _MazeQueue_H_
#include <stdbool.h>

#ifndef _QUEUE_IMPL_


/// maze_node_s is a struct that represents a node on the graph.
typedef struct maze_node_s * MazeNode; 


/// maze_node_s is a struct that represents a queue of MazeNodes. 
typedef struct maze_queue_s * MazeQueue;


#endif


/// Create a MazeQueue and return it 
///
/// @return a MazeQueue instance, or NULL if the allocation fails
MazeQueue que_create(); 


/// creates a new MazeNode and returns a pointer to it
/// @param currentR current row
/// @param currentC current column 
/// @param previousR previous row
/// @param previousC previous column
/// @return MazeNode pointer of the current node
MazeNode que_create_node(unsigned short currentR, unsigned short currentC, short previousR, short previousC); 


/// Tear down and deallocate the supplied QueuADT.
///
/// @param queue - the MazeQueue to be manipulated
void que_destroy( MazeQueue queue );


/// Insert the specified MazeNode into the Queue 
///
/// @param queue the MazeQueue into which the value is to be inserted
/// @param data the data to be inserted
void que_insert( MazeQueue queue, MazeNode data );


/// Return the first element from the MazeQueue.
///
/// @param queue the MazeQueue to be manipulated
/// @return the value that was removed from the queue
/// @exception If the queue is empty, the program will terminate 
///            with an error message.
MazeNode que_next( MazeQueue queue );


/// Finds and returns a Node that once existed in the queue
/// @param queue the queue to check 
/// @param currentR the row of the node to check
/// @param currentC the column of the node to check
/// @return MazeNode when found, null when not 
MazeNode que_find( MazeQueue queue, short currentR, short currentC);


/// Indicate whether or not the supplied Queue is empty
///
/// @param the MazeQueue to be tested
/// @return true if the queue is empty, otherwise false
bool que_empty( MazeQueue queue );


/// gets the currentR from node
/// @param node the node to get data from
/// @return node->currentR
unsigned short node_get_currentR(MazeNode node);


/// gets the currentC from node
/// @param node the node to get data from
/// @return node->currentC
unsigned short node_get_currentC(MazeNode node); 


/// gets the previousR from node
/// @param node the node to get data from
/// @return node->previousR
short node_get_previousR(MazeNode node); 


/// gets the previousC from node
/// @param node the node to get data from
/// @return node->previousC
short node_get_previousC(MazeNode node);


#endif

