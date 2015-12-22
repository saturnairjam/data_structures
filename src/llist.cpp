/**
 * @file  llist.cpp
 *
 * @brief Linked list source.
 */

#include <stdlib.h>
#include <assert.h>

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
    struct llist_node *p_prev;
    struct llist_node *p_next;

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
    struct llist_node *p_node = NULL;

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
    struct llist_node *p_node = NULL;

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
        struct llist_node *p_tmp;

        p_tmp = p_head;

        p_head = p_head->p_next;

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
void llist::delete_tail()
{
    struct llist_node *p_prev = NULL;
    struct llist_node *p_next;

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
 * @brief Remove node with associated value from list.
 *
 * @param[in] value: Value.
 */
void llist::remove(int value)
{
    struct llist_node *p_node;

    p_node = node_find(value);

    if (p_node != NULL)
    {
        struct llist_node *p_prev = NULL;
        struct llist_node *p_next;

        p_next = p_head;

        while (p_next != p_node)
        {
            p_prev = p_next;
            p_next = p_next->p_next;
        }

        if (p_prev != NULL)
        {
            p_prev->p_next = p_node->p_next;
        }
        else
        {
            p_head = p_node->p_next;
        }

        if (p_node == p_tail)
        {
            p_tail = p_prev;
        }

        node_delete(p_node);

        num_nodes--;
    }
}

/**
 * @brief Add node with associated value before specific node.
 *
 * @param[in] p_node: Pointer to node structure before which new node is to be
 *                    added.
 * @param[in] value:  Value.
 */
void llist::add_before(struct llist_node *p_node, int value)
{
    struct llist_node *p_node_new;

    struct llist_node *p_prev = NULL;
    struct llist_node *p_next;

    assert(p_node != NULL);

    p_node_new = node_create(value);

    p_next = p_head;

    while (p_next != p_node)
    {
        p_prev = p_next;
        p_next = p_next->p_next;
    }

    if (p_prev == NULL)
    {
        p_node_new->p_next = p_head;

        p_head = p_node_new;
    }
    else
    {
        p_prev->p_next = p_node_new;

        p_node_new->p_next = p_node;
    }

    num_nodes++;
}

/**
 * @brief Create node with associated value.
 *
 * @param[in] value: Value.
 *
 * @retval Pointer to new node structure.
 */
struct llist_node * llist::node_create(int value)
{
    struct llist_node *p_node = NULL;

    p_node = new llist_node;

    p_node->value = value;

    p_node->p_next = NULL;

    return p_node;
}

/**
 * @brief Delete node.
 *
 * @param[in,out] p_node: Pointer to node structure.
 */
void llist::node_delete(struct llist_node *p_node)
{
    delete p_node;
}

/**
 * @brief Find first node with associated value.
 *
 * @param[in] value: Value.
 *
 * @retval Pointer to node structure.
 */
struct llist_node * llist::node_find(int value)
{
    struct llist_node *p_node;

    bool found = false;

    p_node = p_head;

    while ((p_node != NULL) && (found == false))
    {
        if (p_node->value == value)
        {
            found = true;
        }
        else
        {
            p_node = p_node->p_next;
        }
    }

    if (found)
    {
        return p_node;
    }
    else
    {
        return NULL;
    }
}
