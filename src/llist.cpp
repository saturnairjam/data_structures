/**
 * @file  llist.cpp
 *
 * @brief Linked list source.
 */

#include <stdlib.h>

#include "llist.h"

/**
 * @brief Constructor.
 */
llist::llist()
{
    p_head = NULL;
    p_tail = NULL;

    num_nodes = 0;
}

/**
 * @brief Destructor.
 */
llist::~llist()
{
    struct node *p_prev;
    struct node *p_next;

    p_next = p_head;

    while (p_next != NULL)
    {
        p_prev = p_next;

        p_next = p_next->p_next;

        node_delete(p_prev);

        num_nodes--;
    }

    p_head = NULL;
    p_tail = NULL;
}

/**
 * @brief Add node with associated value to head of list.
 *
 * @param[in] value: Value.
 */
void llist::add_head(int value)
{
    struct node *p_node = NULL;

    p_node = node_create(value);

    p_node->p_next = p_head;

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
void llist::add_tail(int value)
{
    struct node *p_node = NULL;

    p_node = node_create(value);

    if (num_nodes == 0)
    {
        p_head = p_node;
    }
    else
    {
        p_tail->p_next = p_node;
    }

    p_tail = p_node;

    num_nodes++;
}

/**
 * @brief Delete node at head of list.
 */
void llist::delete_head()
{
    if (num_nodes)
    {
        struct node *p_tmp;

        p_tmp = p_head;

        p_head = p_head->p_next;

        if (num_nodes == 1)
        {
            p_tail = NULL;
        }

        node_delete(p_tmp);

        num_nodes--;
    }
}

/**
 * @brief Delete node at tail of list.
 */
void llist::delete_tail()
{
    struct node *p_prev = NULL;
    struct node *p_next;

    p_next = p_head;

    while (p_next != p_tail)
    {
        p_prev = p_next;
        p_next = p_next->p_next;
    }

    p_tail = p_prev;

    if (p_tail != NULL)
    {
        p_tail->p_next = NULL;
    }

    if (p_next != NULL)
    {
        node_delete(p_next);

        num_nodes--;
    }

    if (num_nodes == 0)
    {
        p_head = NULL;
    }
}

/**
 * @brief Create node with associated value.
 *
 * @param[in] value: Value.
 *
 * @retval Pointer to new node structure.
 */
struct node * llist::node_create(int value)
{
    struct node *p_node = NULL;

    p_node = new node;

    p_node->value = value;

    p_node->p_next = NULL;

    return p_node;
}

/**
 * @brief Delete node.
 *
 * @param[in,out] p_node: Pointer to node structure.
 */
void llist::node_delete(struct node *p_node)
{
    delete p_node;
}
