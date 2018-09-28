/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *new_queue = malloc(sizeof(queue_t));
    if(new_queue == NULL) return NULL;
    new_queue->head = new_queue->tail = NULL;
    new_queue->size = 0;
    return new_queue;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(q != NULL)
    {
        list_ele_t *iterator = q->head;
	while(iterator != NULL)
	{
	    list_ele_t *temp = iterator;
	    iterator = temp->next;
	    free(temp);
	}
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(q == NULL) return false;
    list_ele_t *new_node = malloc(sizeof(list_ele_t));
    if(new_node == NULL) return false;
    new_node->value = v;
    new_node->next = q->head;
    q->head = new_node;
    (q->size)++;
    if(q->tail == NULL) q->tail = new_node;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if(q == NULL) return false;
    list_ele_t *new_node = malloc(sizeof(list_ele_t));
    if(new_node == NULL) return false;
    new_node->value = v;
    new_node->next = NULL;
    if(q->tail != NULL) q->tail->next = new_node;
    q->tail = new_node;
    if(q->head == NULL) q->head = new_node;
    (q->size)++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if(q == NULL || q->head == NULL) return false;
    if(vp != NULL) *vp = q->head->value;
    if(q->size == 1) q->tail = NULL;
    list_ele_t *temp = q->head;
    q->head = temp->next;
    (q->size)--;
    free(temp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q == NULL) return 0;
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q) {

    if(q != NULL && q->size > 1) {
        if(q->size == 2) {
	    q->head->next->next = q->head;
	    q->head->next = NULL;
	}
	else {
	    list_ele_t *last_node = q->head;
	    list_ele_t *middle_node = last_node->next;
	    list_ele_t *first_node = middle_node->next;
	    while(first_node->next != NULL) {
	        middle_node->next = last_node;
		last_node = middle_node;
		middle_node = first_node;
		first_node = first_node->next;
	    }
	    first_node->next = middle_node;
	    middle_node->next = last_node;
	    q->head->next = NULL;
	}
	list_ele_t *temp = q->head;
	q->head = q->tail;
	q->tail = temp;
    }
}

