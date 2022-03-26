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
struct maze_node_s
{
    unsigned short currentC; 
    unsigned short currentR; 
    unsigned short previousC; 
    unsigned short previousR; 
}; 

typedef struct maze_node_s * MazeNode; 


/// queue_s is a struct that represents a queue of MazeNodes
struct queue_s 
{
    MazeNode * currentQueue; 
    int currentIndex; 
    int currentLength; 
    int maxSize; 
}; 

typedef struct queue_s * MazeQueue;
#define _QUEUE_IMPL_
#include "MazeQueue.h"


/// Create a MazeQueue that uses the supplied function as a comparison routine.
MazeQueue que_create()
{
    MazeQueue new = (MazeQueue)malloc(sizeof(struct queue_s)); 
    assert(new && "Allocation of new MazeQueue memory failed"); 
    new->currentQueue = (MazeNode)malloc(sizeof(MazeNode)*INITIAL_SIZE);
    assert(new->currentQueue && "Allocation of MazeQueue list memory failed"); 
    new->currentIndex;  
    new->currentLength = 0; 
    new->maxSize = INITIAL_SIZE; 
    return new; 
}


/// Tear down and deallocate the supplied MazeQueue.
void que_destroy( MazeQueue queue )
{
    free(queue->currentQueue); 
    free(queue); 
}


/// Insert the specified data into the Queue in the appropriate place
void que_insert( MazeQueue queue, MazeNode data )
{
    if(queue->currentIndex != queue->maxSize)
    {
        queue->currentQueue[queue->currentIndex + queue->currentLength] = data;
        queue->currentLength++; 
    }
    else
    {
        MazeNode temp = (MazeNode)realloc(queue->currentQueue, (sizeof(queue->currentQueue)*2)); 
        queue->currentQueue = temp; 
        assert(queue->currentQueue && "Reallocation of memory failed"); 
        queue->maxSize = queue->maxSize * 2; 
        que_insert(queue, data); 
    }
} 


/// Return the first element from the queue.
MazeNode que_next( MazeQueue queue )
{
    assert(queue->currentLength != 0 && "Cannot remove from an empty queue"); 
    return queue->currentQueue[queue->currentIndex++]; 
}   


/// Indicates if the queue has ever had or currently has a MazeNode 
bool que_has_or_had( MazeQueue queue, MazeNode node )
{
    for(int i = 0; i < queue->currentIndex + queue->currentLength; i++)
    {
        if(queue->currentQueue[i]->currentC == node->currentC &&
           queue->currentQueue[i]->currentR == node->currentR)
                return true; 
    }
    return false; 
}


/// Indicate whether or not the supplied Queue is empty
bool que_empty( MazeQueue queue )
{
    return (queue->currentLength == 0);  
}

