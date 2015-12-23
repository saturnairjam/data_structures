/**
 * @file  btree.h
 *
 * @brief Binary tree header.
 */

#ifndef _BTREE_H_

#define _BTREE_H_

/// binary tree node structure
struct btree_node {
    int                value;   ///< node value
    struct btree_node *p_left;  ///< pointer to left child node
    struct btree_node *p_right; ///< pointer to right child node
};

/// binary tree class
class btree
{
public:

    btree();
    ~btree();

    void add(int value);

    struct btree_node *p_root; ///< pointer to root node

private:

    void add(struct btree_node *p_node, int value);

    struct btree_node *node_create(int value);
    void               node_delete(struct btree_node *p_node);

    int num_nodes; ///< number of nodes in tree
};

#endif // #ifndef _BTREE_H_
