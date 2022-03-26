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
/// currentC represents the current column 
/// currentR represents the current row
/// previousC represents the previous column 
/// previousR represents the previous row 
typedef struct maze_node_s
{
    unsigned short currentC; 
    unsigned short currentR; 
    unsigned short previousC; 
    unsigned short previousR; 
} * MazeNode; 


/// maze_node_s is a struct that represents a node on the graph. 
/// currentC represents the current nodes x coodinate
/// currentR represents the current nodes y coodinate
/// prviousC represents the previous nodes x coodinate
/// prviousR represents the previous nodes y coodinate
typedef struct 
{
    MazeNode* currentQueue; 
    int currentSize; 
    int maxSize; 
} * MazeQueue;




#endif


/// Create a MazeQueue and return it 
///
/// @return a MazeQueue instance, or NULL if the allocation fails
MazeQueue que_create(); 


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
///     with an error message.
MazeNode que_next( MazeQueue queue );

/// Indicates if the queue has ever had or currently has a MazeNode
/// @param queue the queue to check 
/// @param node the node to check if has existed in the queue
bool que_has_or_had( MazeQueue queue, MazeNode node ); 


/// Indicate whether or not the supplied Queue is empty
///
/// @param the MazeQueue to be tested
/// @return true if the queue is empty, otherwise false
bool que_empty( MazeQueue queue );


#endif

