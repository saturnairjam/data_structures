/**
 * @file  queue.h
 *
 * @brief Queue header.
 */

#ifndef _QUEUE_H_

#define _QUEUE_H_

#include "llist.h"

/// queue class
class queue
{
public:

    queue();
    ~queue();

    void enqueue(int value);
    int  dequeue();

    llist *p_llist; ///< pointer to linked list

private:

    int num_items; ///< number of items in queue
};

#endif // #ifndef _QUEUE_H_
