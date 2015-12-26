/**
 * @file  dllist.h
 *
 * @brief Doubly-linked list class.
 */

#ifndef _DLLIST_H_

#define _DLLIST_H_

/// doubly-linked list node structure
template <typename T>
struct dllist_node {
    T               value;  ///< node value
    dllist_node<T> *p_next; ///< pointer to next node
    dllist_node<T> *p_prev; ///< pointer to previous node
};

/// doubly-linked list class
template <typename T>
class dllist
{
public:

    /**
     * @brief Constructor.
     */
    dllist()
    {
        p_head = NULL;
        p_tail = NULL;

        num_nodes = 0;
    }

    /**
     * @brief Destructor.
     */
    ~dllist()
    {
        dllist_node<T> *p_prev;
        dllist_node<T> *p_next;

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
    void add_head(T value)
    {
        dllist_node<T> *p_node = NULL;

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
    void add_tail(T value)
    {
        dllist_node<T> *p_node = NULL;

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
    void delete_head()
    {
        if (num_nodes)
        {
            dllist_node<T> *p_temp;

            p_temp = p_head;

            p_head = p_head->p_next;

            if (p_head != NULL)
            {
                p_head->p_prev = NULL;
            }

            node_delete(p_temp);

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
    void delete_tail()
    {
        if (num_nodes)
        {
            dllist_node<T> *p_temp;

            p_temp = p_tail;

            p_tail = p_tail->p_prev;

            if (p_tail != NULL)
            {
                p_tail->p_next = NULL;
            }

            node_delete(p_temp);

            num_nodes--;

            if (num_nodes == 0)
            {
                p_head = NULL;
            }
        }
    }

    /**
     * @brief Remove node with associated value from list.
     *
     * @param[in] value: Value.
     */
    void remove(T value)
    {
        dllist_node<T> *p_node;

        p_node = node_find(value);

        if (p_node != NULL)
        {
            dllist_node<T> *p_prev = NULL;
            dllist_node<T> *p_next;

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

            if (p_node->p_next != NULL)
            {
                p_node->p_next->p_prev = p_prev;
            }

            if (p_node == p_head)
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

    dllist_node<T> *p_head; ///< pointer to head node

private:

    /**
     * @brief Create node with associated value.
     *
     * @param[in] value: Value.
     *
     * @retval Pointer to new node structure.
     */
    dllist_node<T> *node_create(T value)
    {
        dllist_node<T> *p_node = NULL;

        p_node = new dllist_node<T>;

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
    void node_delete(dllist_node<T> *p_node)
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
    dllist_node<T> *node_find(T value)
    {
        dllist_node<T> *p_node;

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

    dllist_node<T> *p_tail; ///< pointer to tail node

    int num_nodes; ///< number of nodes in list
};

#endif // #ifndef _DLLIST_H_
