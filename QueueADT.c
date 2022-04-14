// File: QueueADT.c
//
// Description:  Implementation of the QueueADT module. A queue is a data set
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
#define INITIAL_SIZE 64

/// queue_s is a struct that represents a queue data structure whose payload
/// data type is 'generic'. 
/// currentQueue represents the queue 
/// currentSize represents the number of items in the queue
/// maxSize represents the maximum number of items that can fit in the queue 
/// given the current memory allocation
/// cmp represents a pointer to the compare function that this ADT uses to
/// order the queue
struct queue_s 
{
    void ** currentQueue; 
    int currentSize; 
    int maxSize; 
}; 


typedef struct queue_s * QueueADT;
#define _QUEUE_IMPL_
#include "QueueADT.h"


/// Create a QueueADT that uses the supplied function as a comparison routine.
QueueADT que_create()
{
    QueueADT new = (QueueADT)malloc(sizeof(struct queue_s)); 
    assert(new && "Allocation of new QueueADT memory failed"); 
    new->currentQueue = (void *)malloc(sizeof(void*)*INITIAL_SIZE);
    assert(new->currentQueue && "Allocation of QueueADT list memory failed");  
    new->currentSize = 0; 
    new->maxSize = INITIAL_SIZE; 
    return new; 
}


/// Tear down and deallocate the supplied QueueADT.
void que_destroy( QueueADT queue )
{
    free(queue->currentQueue); 
    free(queue); 
}


/// Remove all contents from the supplied QueueADT.
void que_clear( QueueADT queue )
{
    free(queue->currentQueue); 
    queue->currentQueue = (void *)malloc(sizeof(void*)*INITIAL_SIZE);
}


/// Insert the specified data into the Queue in the appropriate place
void que_insert( QueueADT queue, void * data )
{
    if(queue->currentSize != queue->maxSize)
    {
        queue->currentQueue[queue->currentSize] = data;
        queue->currentSize++; 
    }
    else
    {
        void * temp = (void *)realloc(queue->currentQueue, (sizeof(void *)*(queue->maxSize + INITIAL_SIZE))); 
        queue->currentQueue = temp; 
        assert(queue->currentQueue && "Reallocation of memory failed"); 
        queue->maxSize = queue->maxSize + INITIAL_SIZE; 
        que_insert(queue, data); 
    }
} 


/// Remove and return the first element from the QueueADT.
void * que_remove( QueueADT queue )
{
    assert(queue->currentSize != 0 && "Cannot remove from an empty queue"); 
    void * rValue = queue->currentQueue[0];
    for(int i = 0; i < queue->currentSize; i++)
    {
        queue->currentQueue[i] = queue->currentQueue[i+1]; 
    }
    queue->currentSize--; 
    return rValue; 
}   


/// Indicate whether or not the supplied Queue is empty
bool que_empty( QueueADT queue )
{
    return (queue->currentSize == 0);  
}

