/**
 * @file  btree.h
 *
 * @brief Binary tree class.
 */

#ifndef _BTREE_H_

#define _BTREE_H_

/// binary tree node structure
template <typename T>
struct btree_node {
    T              value;   ///< node value
    btree_node<T> *p_left;  ///< pointer to left child node
    btree_node<T> *p_right; ///< pointer to right child node
};

/// binary tree class
template <typename T>
class btree
{
public:

    /**
     * @brief Constructor.
     */
    btree()
    {
        p_root = NULL;

        num_nodes = 0;
    }

    /**
     * @brief Destructor.
     */
    ~btree()
    {
        btree_delete(p_root);
    }

    /**
     * @brief Add node with associated value to tree.
     *
     * @param[in] value: Value.
     */
    void add(T value)
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
     * @brief Find node with associated value.
     *
     * @param[in] p_node: Pointer to sub-tree's root node.
     * @param[in] value:  Value.
     *
     * @retval NULL if node not found.
     * @retval Pointer to node with associated value.
     */
    btree_node<T> *find(btree_node<T> *p_node, T value)
    {
        if (p_node == NULL)
        {
            return NULL;
        }
        else if (p_node->value == value)
        {
            return p_node;
        }
        else if (value < p_node->value)
        {
            return find(p_node->p_left, value);
        }
        else
        {
            return find(p_node->p_right, value);
        }
    }

    btree_node<T> *p_root; ///< pointer to root node

private:

    /**
     * @brief Recursive function to add node with associated value to sub-tree.
     *
     * @param[in,out] p_node: Pointer to sub-tree's root node.
     * @param[in]     value:  Value.
     */
    void add(btree_node<T> *p_node, T value)
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
    btree_node<T> *node_create(T value)
    {
        btree_node<T> *p_node = NULL;

        p_node = new btree_node<T>;

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
    void node_delete(btree_node<T> *p_node)
    {
        delete p_node;

        num_nodes--;
    }

    /**
     * @brief Recursively delete binary tree using post-order traversal.
     *
     * @param[in,out] p_node: Pointer to node structure (current sub-tree's
     *                        root node).
     */
    void btree_delete(btree_node<T> *p_node)
    {
        if (p_node != NULL)
        {
            btree_delete(p_node->p_left);
            btree_delete(p_node->p_right);

            delete p_node;

            num_nodes--;
        }
    }

    int num_nodes; ///< number of nodes in tree
};

#endif // #ifndef _BTREE_H_
