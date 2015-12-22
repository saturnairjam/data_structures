/**
 * @file  pqueue.cpp
 *
 * @brief Priority queue source.
 */

#include <stdlib.h>
#include <assert.h>

#include "pqueue.h"

/**
 * @brief Constructor.
 */
pqueue::pqueue()
{
    p_llist = new llist;

    num_items = 0;
}

/**
 * @brief Destructor.
 */
pqueue::~pqueue()
{
    delete p_llist;
}

/**
 * @brief Enqueue value in ascending order.
 *
 * @param[in] value: Value.
 */
void pqueue::enqueue(int value)
{
    struct llist_node *p_node;

    p_node = p_llist->p_head;

    while (p_node != NULL)
    {
        if (value < p_node->value)
        {
            break;
        }

        p_node = p_node->p_next;
    }

    if (p_node == NULL)
    {
        p_llist->add_tail(value);
    }
    else
    {
        p_llist->add_before(p_node, value);
    }

    num_items++;
}

/**
 * @brief Dequeue value.
 *
 * @retval Value at head of priority queue.
 */
int pqueue::dequeue()
{
    int value;

    assert(num_items > 0);

    value = p_llist->p_head->value;

    p_llist->delete_head();

    return value;
}
