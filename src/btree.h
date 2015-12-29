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
     * @retval NULL if node with associated value not found.
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

    /**
     * @brief Remove node with associated value.
     *
     * @param[in] value: Value.
     *
     * @retval  true if node with associated value removed.
     * @retval false if node with associated value not removed.
     */
    bool remove(T value)
    {
        bool node_removed = false;

        btree_node<T> *p_node_current;
        btree_node<T> *p_node_parent;

        p_node_current = find_node_and_parent(&p_node_parent, value);

        if (p_node_current != NULL)
        {
            /**
             * Case 1: Current node has no right child.
             *
             * - Current node's left child replaces it.
             */
            if (p_node_current->p_right == NULL)
            {
                if (p_node_parent == NULL)
                {
                    p_root = p_node_current->p_left;
                }
                else
                {
                    if (p_node_current->value < p_node_parent->value)
                    {
                        // current node is it's parent's left child

                        p_node_parent->p_left = p_node_current->p_left;
                    }
                    else
                    {
                        // current node is it's parent's right child

                        p_node_parent->p_right = p_node_current->p_left;
                    }
                }

                node_delete(p_node_current);

                node_removed = true;
            }

            /**
             * Case 2: Current node's right child has no left child.
             *
             * - Current node's right child replaces it.
             */
            else if (p_node_current->p_right->p_left == NULL)
            {
                p_node_current->p_right->p_left = p_node_current->p_left;

                if (p_node_parent == NULL)
                {
                    p_root = p_node_current->p_right;
                }
                else
                {
                    if (p_node_current->value < p_node_parent->value)
                    {
                        // current node is it's parent's left child

                        p_node_parent->p_left = p_node_current->p_right;
                    }
                    else
                    {
                        // current node is it's parent's right child

                        p_node_parent->p_right = p_node_current->p_right;
                    }
                }

                node_delete(p_node_current);

                node_removed = true;
            }

            /**
             * Case 3: Current node's right child has a left child.
             *
             * - Current node's right child's left-most child replaces it.
             */
            else
            {
                // find right child's left-most child & it's parent

                btree_node<T> *p_node_leftmost;
                btree_node<T> *p_node_leftmost_parent;

                p_node_leftmost        = p_node_current->p_right->p_left;
                p_node_leftmost_parent = p_node_current->p_right;

                while (p_node_leftmost->p_left != NULL)
                {
                    p_node_leftmost_parent = p_node_leftmost;

                    p_node_leftmost = p_node_leftmost->p_left;
                }

                // left-most's right subtree becomes it's parent's left subtree

                p_node_leftmost_parent->p_left = p_node_leftmost->p_right;

                // re-assign current node's left & right children

                p_node_leftmost->p_left  = p_node_current->p_left;
                p_node_leftmost->p_right = p_node_current->p_right;

                if (p_node_parent == NULL)
                {
                    p_root = p_node_leftmost;
                }
                else
                {
                    if (p_node_current->value < p_node_parent->value)
                    {
                        // current node is it's parent's left child

                        p_node_parent->p_left = p_node_leftmost;
                    }
                    else
                    {
                        // current node is it's parent's right child

                        p_node_parent->p_right = p_node_leftmost;
                    }
                }

                node_delete(p_node_current);

                node_removed = true;
            }
        }

        return node_removed;
    }

    /**
     * @brief Get depth of sub-tree recursively.
     *
     * @param[in] p_node: Pointer to sub-tree's root node.
     *
     * @retval Depth of sub-tree.
     */
    int depth(btree_node<T> *p_node)
    {
        if (p_node == NULL)
        {
            return 0;
        }
        else
        {
            int depth_left  = depth(p_node->p_left);
            int depth_right = depth(p_node->p_right);

            return ((depth_left > depth_right) ? depth_left : depth_right) + 1;
        }
    }

    /**
     * @brief Verify tree by traversing it in-order and checking that no element
     *        is greater than it's predecessor.
     *
     * @param[in] p_node:     Pointer to sub-tree's root node.
     * @param[in] value_prev: Previous value.
     *
     * @retval  true if binary tree is correct
     * @retval false if binary tree is incorrect
     */
    bool verify(btree_node<T> *p_node, T value_prev)
    {
        bool retval = true;

        if (p_node != NULL)
        {
            retval = verify(p_node->p_left, value_prev);

            if (retval == true)
            {
                if (p_node->value < value_prev)
                {
                    retval = false;
                }
                else
                {
                    value_prev = p_node->value;

                    retval = verify(p_node->p_right, value_prev);
                }
            }
        }

        return retval;
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
     * @brief Find node with associated value and it's parent node.
     *
     * @param[in,out] pp_node_parent: Pointer to pointer to parent node of node
     *                                with associated value.
     * @param[in]     value:          Value.
     *
     * @retval NULL if node with associated value not found.
     * @retval Pointer to node with associated value.
     */
    btree_node<T> *find_node_and_parent(btree_node<T> **pp_node_parent, T value)
    {
        btree_node<T> *p_node_current;

        p_node_current = p_root;

        *pp_node_parent = NULL;

        while (p_node_current != NULL)
        {
            if (value < p_node_current->value)
            {
                *pp_node_parent = p_node_current;

                p_node_current = p_node_current->p_left;
            }
            else if (value == p_node_current->value)
            {
                break;
            }
            else
            {
                *pp_node_parent = p_node_current;

                p_node_current = p_node_current->p_right;
            }
        }

        return p_node_current;
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
