/**
 * @file  pqueue.h
 *
 * @brief Priority queue header.
 */

#ifndef _PQUEUE_H_

#define _PQUEUE_H_

#include "llist.h"

/// priority queue class
class pqueue
{
public:

    pqueue();
    ~pqueue();

    void enqueue(int value);
    int  dequeue();

    bool is_empty();

    llist *p_llist; ///< pointer to linked list

private:

    int num_items; ///< number of items in queue
};

#endif // #ifndef _PQUEUE_H_
