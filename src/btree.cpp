/**
 * @file  btree.cpp
 *
 * @brief Binary tree source.
 */

#include <stdlib.h>

#include "btree.h"

/**
 * @brief Constructor.
 */
btree::btree()
{
    p_root = NULL;

    num_nodes = 0;
}

/**
 * @brief Destructor.
 */
btree::~btree()
{
}

/**
 * @brief Add node with associated value to tree.
 *
 * @param[in] value: Value.
 */
void btree::add(int value)
{
    if (p_root == NULL)
    {
        p_root = node_create(value);
    }
    else
    {
        add(p_root, value);
    }

    num_nodes++;
}

/**
 * @brief Recursive function to add node with associated value to sub-tree.
 *
 * @param[in,out] p_node: Pointer to sub-tree's root node.
 * @param[in]     value:  Value.
 */
void btree::add(struct btree_node *p_node, int value)
{
    if (value < p_node->value)
    {
        if (p_node->p_left == NULL)
        {
            p_node->p_left = node_create(value);
        }
        else
        {
            add(p_node->p_left, value);
        }
    }
    else
    {
        if (p_node->p_right == NULL)
        {
            p_node->p_right = node_create(value);
        }
        else
        {
            add(p_node->p_right, value);
        }
    }
}

/**
 * @brief Create node with associated value.
 *
 * @param[in] value: Value.
 *
 * @retval Pointer to new node structure.
 */
struct btree_node * btree::node_create(int value)
{
    struct btree_node *p_node = NULL;

    p_node = new btree_node;

    p_node->value = value;

    p_node->p_left  = NULL;
    p_node->p_right = NULL;

    return p_node;
}

/**
 * @brief Delete node.
 *
 * @param[in,out] p_node: Pointer to node structure.
 */
void btree::node_delete(struct btree_node *p_node)
{
    delete p_node;
}
