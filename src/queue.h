/**
 * @file  queue.h
 *
 * @brief Queue class.
 */

#ifndef _QUEUE_H_

#define _QUEUE_H_

#include "llist.h"

/// queue class
template <typename T>
class queue
{
public:

    /**
     * @brief Constructor.
     */
    queue()
    {
        p_llist = new llist<T>;

        num_items = 0;
    }

    /**
     * @brief Destructor.
     */
    ~queue()
    {
        delete p_llist;
    }

    /**
     * @brief Enqueue value.
     *
     * @param[in] value: Value.
     */
    void enqueue(T value)
    {
        p_llist->add_tail(value);

        num_items++;
    }

    /**
     * @brief Dequeue value.
     *
     * @retval Value at top of stack.
     */
    T dequeue()
    {
        T value;

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
    bool is_empty()
    {
        return (num_items == 0) ? true : false;
    }

    llist<T> *p_llist; ///< pointer to linked list

private:

    int num_items; ///< number of items in queue
};

#endif // #ifndef _QUEUE_H_
