/**
 * @file  stack.h
 *
 * @brief Stack header.
 */

#ifndef _STACK_H_

#define _STACK_H_

#include "llist.h"

/// stack class
class stack
{
public:

    stack();
    ~stack();

    void push(int value);
    int  pop();
    int  peek();

    llist *p_llist; ///< pointer to linked list

private:

    int num_items; ///< number of items in stack
};

#endif // #ifndef _STACK_H_
