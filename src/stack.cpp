/**
 * @file  stack.cpp
 *
 * @brief Stack source.
 */

#include <stdlib.h>

#include "stack.h"

/**
 * @brief Constructor.
 */
stack::stack()
{
    p_llist = new llist;
}

/**
 * @brief Destructor.
 */
stack::~stack()
{
    delete p_llist;
}

/**
 * @brief Push value onto stack.
 *
 * @param[in] value: Value.
 */
void stack::push(int value)
{
    p_llist->add_head(value);
}

/**
 * @brief Pop value from stack.
 *
 * @retval Value at top of stack.
 */
int stack::pop()
{
    int value = 0;

    if (p_llist->p_head != NULL)
    {
        value = p_llist->p_head->value;

        p_llist->delete_head();
    }

    return value;
}

/**
 * @brief Peek value at top of stack.
 *
 * @retval Value at top of stack.
 */
int stack::peek()
{
    int value = 0;

    if (p_llist->p_head != NULL)
    {
        value = p_llist->p_head->value;
    }

    return value;
}
