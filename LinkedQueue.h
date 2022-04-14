// File: LinkedQueue.h
//
// Description:  Interface to the LinkedQueue module
//
// Author:  Ryan Current rjc7379
//

#ifndef _LINKED_QUEUE_H
#define _LINKED_QUEUE_H

#ifndef _QUEUE_IMPL_

/// abstract queue data type that represents a linked queue
typedef struct queue_s * LinkedQueue;

#endif

/// allocates memory and creates a queue
/// @return a pointer linkedqueue
LinkedQueue que_create();


/// returns weather the queue is empty or not 
/// @param queue the queue to check if empty
/// @return true when the queue is empty
bool que_empty(LinkedQueue queue);


/// inserts a data value into the queue
/// @param data the data to insert 
/// @param queue the queue to insert data into
void que_insert(LinkedQueue queue, void * data);


/// gets the next item from the queue
/// @param queue the queue to get the item from 
/// @return the next data value
void * que_pop(LinkedQueue queue); 


/// destroys and deallocates memory associated with the queue
/// @param queue the queue to deallocate and destory
void que_destroy(LinkedQueue queue); 


#endif
