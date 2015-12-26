/**
 * @file  stack.h
 *
 * @brief Stack class.
 */

#ifndef _STACK_H_

#define _STACK_H_

#include "llist.h"

/// stack class
template <typename T>
class stack
{
public:

    /**
     * @brief Constructor.
     */
    stack()
    {
        p_llist = new llist<T>;
    }

    /**
     * @brief Destructor.
     */
    ~stack()
    {
        delete p_llist;
    }

    /**
     * @brief Push value onto stack.
     *
     * @param[in] value: Value.
     */
    void push(T value)
    {
        p_llist->add_head(value);
    }

    /**
     * @brief Pop value from stack.
     *
     * @retval Value at top of stack.
     */
    T pop()
    {
        T value;

        assert(p_llist->p_head != NULL);

        value = p_llist->p_head->value;

        p_llist->delete_head();

        return value;
    }

    /**
     * @brief Peek value at top of stack.
     *
     * @retval Value at top of stack.
     */
    T peek()
    {
        assert(p_llist->p_head != NULL);

        return p_llist->p_head->value;
    }

    llist<T> *p_llist; ///< pointer to linked list
};

#endif // #ifndef _STACK_H_
