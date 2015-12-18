/**
 * @file  dllist.cpp
 *
 * @brief Doubly-linked list source.
 */

#include <stdlib.h>

#include "dllist.h"

/**
 * @brief Constructor.
 */
dllist::dllist()
{
    p_head = NULL;
    p_tail = NULL;

    num_nodes = 0;
}

/**
 * @brief Destructor.
 */
dllist::~dllist()
{
}

/**
 * @brief Add node with associated value to head of list.
 *
 * @param[in] value: Value.
 */
void dllist::add_head(int value)
{
    struct dllist_node *p_node = NULL;

    p_node = node_create(value);

    p_node->p_next = p_head;
    p_node->p_prev = NULL;

    if (p_head != NULL)
    {
        p_head->p_prev = p_node;
    }

    p_head = p_node;

    if (num_nodes == 0)
    {
        p_tail = p_node;
    }

    num_nodes++;
}

/**
 * @brief Add node with associated value to tail of list.
 *
 * @param[in] value: Value.
 */
void dllist::add_tail(int value)
{
    struct dllist_node *p_node = NULL;

    p_node = node_create(value);

    if (num_nodes)
    {
        p_tail->p_next = p_node;
    }

    p_node->p_next = NULL;
    p_node->p_prev = p_tail;

    p_tail = p_node;

    if (num_nodes == 0)
    {
        p_head = p_node;
    }

    num_nodes++;
}

/**
 * @brief Delete node at head of list.
 */
void dllist::delete_head()
{
    if (num_nodes)
    {
        struct dllist_node *p_tmp;

        p_tmp = p_head;

        p_head = p_head->p_next;

        if (p_head != NULL)
        {
            p_head->p_prev = NULL;
        }

        node_delete(p_tmp);

        num_nodes--;

        if (num_nodes == 0)
        {
            p_tail = NULL;
        }
    }
}

/**
 * @brief Delete node at tail of list.
 */
void dllist::delete_tail()
{
    if (num_nodes == 2)
    {
        volatile int tmp = 1;

        (void) tmp;
    }

    if (num_nodes)
    {
        struct dllist_node *p_tmp;

        p_tmp = p_tail;

        p_tail = p_tail->p_prev;

        if (p_tail != NULL)
        {
            p_tail->p_next = NULL;
        }

        node_delete(p_tmp);

        num_nodes--;

        if (num_nodes == 0)
        {
            p_head = NULL;
        }
    }
}

/**
 * @brief Create node with associated value.
 *
 * @param[in,out] value: Value.
 *
 * @retval Pointer to new node structure.
 */
struct dllist_node * dllist::node_create(int value)
{
    struct dllist_node *p_node = NULL;

    p_node = new dllist_node;

    p_node->value  = value;
    p_node->p_next = NULL;
    p_node->p_prev = NULL;

    return p_node;
}

/**
 * @brief Delete node.
 *
 * @param[in,out] p_node: Pointer to node structure.
 */
void dllist::node_delete(struct dllist_node *p_node)
{
    delete p_node;
}
