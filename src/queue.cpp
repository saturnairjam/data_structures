/**
 * @file  queue.cpp
 *
 * @brief Queue source.
 */

#include <stdlib.h>
#include <assert.h>

#include "queue.h"

/**
 * @brief Constructor.
 */
queue::queue()
{
    p_llist = new llist;

    num_items = 0;
}

/**
 * @brief Destructor.
 */
queue::~queue()
{
    delete p_llist;
}

/**
 * @brief Enqueue value.
 *
 * @param[in] value: Value.
 */
void queue::enqueue(int value)
{
    p_llist->add_tail(value);

    num_items++;
}

/**
 * @brief Dequeue value.
 *
 * @retval Value at head of queue.
 */
int queue::dequeue()
{
    int value;

    assert(num_items > 0);

    value = p_llist->p_head->value;

    p_llist->delete_head();

    num_items--;

    return value;
}

/**
 * @brief Is queue empty?
 *
 * @retval  true if queue is empty
 * @retval false if queue is not empty
 */
bool queue::is_empty()
{
    return (num_items == 0) ? true : false;
}
