// File: LinkedQueue.c
//
// Description:  Implementation of the LinkedQueue module. A queue is a data 
//               set that contains a list of void* data memebers that can be 
//               popped and used. 
// 
// Author:  Ryan Current rjc7379
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


/// data type that represents a current node 
/// data is the current data 
/// next is the next node 
typedef struct queue_node_s 
{
    void * data;
    struct queue_node_s * next;
} * QueueNode;


/// abstract queue data type that represents a linked queue
/// head is the beginning 
/// tail is the end 
/// size is the size of the queue
typedef struct queue_s
{
    QueueNode head;
    QueueNode tail; 
    int size;  
} * LinkedQueue;

#define _QUEUE_IMPL_
#include "LinkedQueue.h"


/// allocates memory and creates a node with the data specified
/// @param data the data to insert
/// @return a created QueueNode
QueueNode node_create(void * data)
{
    QueueNode new = malloc(sizeof(struct queue_node_s));
    assert(new && "Node memory allocation failed"); 
    new->data = data;
    return new;
}


/// allocates memory and creates a queue
LinkedQueue que_create() 
{
    LinkedQueue queue = malloc(sizeof(struct queue_s));
    assert(queue && "Queue memory allocation failed"); 
    queue->head = NULL;
    queue->size = 0; 
    return queue;
}


/// returns weather the queue is empty or not
bool que_empty(LinkedQueue queue)
{
    return queue->size == 0; 
}


/// inserts a data value into the queue
void que_insert(LinkedQueue queue, void * data)
{
    if(queue->size == 0)
    {
        queue->head = node_create(data);
        queue->tail = queue->head; 
    }
    else 
    {
        queue->tail->next = node_create(data); 
        queue->tail = queue->tail->next; 
    }
    queue->size = queue->size + 1; 
}


/// gets the next item from the queue
void * que_pop(LinkedQueue queue)  
{
    assert(!que_empty(queue) && "Error: cannot remove from empty queue"); 
    void * rVal = queue->head->data;
    QueueNode newHead = queue->head->next; 
    free(queue->head); 
    queue->head = newHead; 
    queue->size = queue->size - 1; 
    return rVal; 
}    


/// destroys and deallocates memory associated with the queue
void que_destroy(LinkedQueue queue)
{
    if(queue)
        free(queue);
}
