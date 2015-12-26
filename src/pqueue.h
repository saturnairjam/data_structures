/**
 * @file  pqueue.h
 *
 * @brief Priority queue class.
 */

#ifndef _PQUEUE_H_

#define _PQUEUE_H_

#include "llist.h"

/// queue class
template <typename T>
class pqueue
{
public:

    /**
     * @brief Constructor.
     */
    pqueue()
    {
        p_llist = new llist<T>;

        num_items = 0;
    }

    /**
     * @brief Destructor.
     */
    ~pqueue()
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
        llist_node<T> *p_node;

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

#endif // #ifndef _PQUEUE_H_
