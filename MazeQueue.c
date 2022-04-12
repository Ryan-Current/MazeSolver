// File: MazeQueue.c
//
// Description:  Implementation of the MazeQueue module. A queue is a data set
//               that contains a list of void* data memebers that is ordered 
//               based on the *cmp function that gets passed in when creating 
//               the data structure. 
// 
// Author:  Ryan Current rjc7379
//


#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define INITIAL_SIZE 2


/// maze_node_s is a struct that represents a node on the graph.
/// currentC represents the current column 
/// currentR represents the current row
/// previousC represents the previous column 
/// previousR represents the previous row  
struct maze_node_s
{
    unsigned short currentR; 
    unsigned short currentC; 
    short previousR; 
    short previousC; 
}; 

typedef struct maze_node_s * MazeNode; 


/// queue_s is a struct that represents a queue of MazeNodes. 
/// currentQueue represents the current queue of MazeNodes. 
/// currentStart represents the current start index 
/// currentEnd represents the current last index 
/// maxSize represents the maximum number of nodes that can
struct maze_queue_s 
{
    MazeNode * currentQueue; 
    int currentStart; 
    int currentEnd; 
    int maxSize; 
}; 

typedef struct maze_queue_s * MazeQueue;
#define _QUEUE_IMPL_
#include "MazeQueue.h"


/// Create a MazeQueue that uses the supplied function as a comparison routine.
MazeQueue que_create()
{
    MazeQueue new = (MazeQueue)malloc(sizeof(struct maze_queue_s)); 
    assert(new && "Allocation of new MazeQueue memory failed"); 
    new->currentQueue = (MazeNode *)malloc(sizeof(MazeNode)*INITIAL_SIZE);
    assert(new->currentQueue && "Allocation of MazeQueue list memory failed"); 
    new->currentStart = 0;  
    new->currentEnd = 0; 
    new->maxSize = INITIAL_SIZE; 
    return new; 
}

/// creates a new MazeNode and returns a pointer to it
MazeNode que_create_node(unsigned short currentR, unsigned short currentC, short previousR, short previousC)
{
    MazeNode new = (MazeNode)malloc(sizeof(struct maze_node_s)); 
    new->currentR = currentR; 
    new->currentC = currentC; 
    new->previousR = previousR; 
    new->previousC = previousC; 
    return new; 
}


/// Tear down and deallocate the supplied MazeQueue.
void que_destroy( MazeQueue queue )
{
    for(int i = 0; i < queue->currentEnd; i++)
    {
        free(queue->currentQueue[i]); 
    }
    free(queue->currentQueue); 
    free(queue); 
}



/// Insert the specified node into the Queue in the appropriate place
void que_insert( MazeQueue queue, MazeNode node )
{
    if(queue->currentEnd != queue->maxSize)
    {
        queue->currentQueue[queue->currentEnd] = node;
        queue->currentEnd++; 
    }
    else
    {
        MazeNode * temp = (MazeNode *)realloc(queue->currentQueue, 2 * queue->maxSize * sizeof(MazeNode)); 
        queue->currentQueue = temp; 
        assert(queue->currentQueue && "Reallocation of memory failed"); 
        queue->maxSize = queue->maxSize * 2; 
        que_insert(queue, node); 
    }
} 


/// Indicate whether or not the supplied Queue is empty
bool que_empty( MazeQueue queue )
{
    return (queue->currentEnd == queue->currentStart);  
}


/// Return the first element from the queue.
MazeNode que_next( MazeQueue queue )
{
    assert(!que_empty(queue) && "Cannot remove from an empty queue"); 
    MazeNode nextNode = queue->currentQueue[queue->currentStart];
    queue->currentStart++; 
    return nextNode; 
}   


/// Finds and returns a Node that once existed in the queue
MazeNode que_find( MazeQueue queue, short currentR, short currentC)
{
    for(int i = queue->currentEnd - 1; i > 0; i--)
    {
        if(queue->currentQueue[i]->currentC == currentC &&
           queue->currentQueue[i]->currentR == currentR)
                return queue->currentQueue[i]; 
    }
    return NULL; 
}


/// gets the currentR from node
unsigned short node_get_currentR(MazeNode node)
{
    return node->currentR; 
}


/// gets the currentC from node
unsigned short node_get_currentC(MazeNode node)
{
    return node->currentC; 
}


/// gets the previousR from node
short node_get_previousR(MazeNode node)
{
    return node->previousR; 
}


/// gets the previousC from node
short node_get_previousC(MazeNode node)
{
    return node->previousC; 
}




