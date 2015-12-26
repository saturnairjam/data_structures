/**
 * @file  llist.h
 *
 * @brief Linked list class.
 */

#ifndef _LLIST_H_

#define _LLIST_H_

#include <assert.h>

/// linked list node structure
template <typename T>
struct llist_node {
    T              value;  ///< node value
    llist_node<T> *p_next; ///< pointer to next node
};

/// linked list class
template <typename T>
class llist
{
public:

    /**
     * @brief Constructor.
     */
    llist()
    {
        p_head = NULL;
        p_tail = NULL;

        num_nodes = 0;
    }

    /**
     * @brief Destructor.
     */
    ~llist()
    {
        llist_node<T> *p_prev;
        llist_node<T> *p_next;

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
        llist_node<T> *p_node = NULL;

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
    void add_tail(T value)
    {
        llist_node<T> *p_node = NULL;

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
    void delete_head()
    {
        if (num_nodes)
        {
            llist_node<T> *p_temp;

            p_temp = p_head;

            p_head = p_head->p_next;

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
        llist_node<T> *p_prev = NULL;
        llist_node<T> *p_next;

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
    void remove(T value)
    {
        llist_node<T> *p_node;

        p_node = node_find(value);

        if (p_node != NULL)
        {
            llist_node<T> *p_prev = NULL;
            llist_node<T> *p_next;

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
     * @param[in] p_node: Pointer to node structure before which new node is to
     *                    be added.
     * @param[in] value:  Value.
     */
    void add_before(llist_node<T> *p_node, T value)
    {
        llist_node<T> *p_node_new;

        llist_node<T> *p_prev = NULL;
        llist_node<T> *p_next;

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

    llist_node<T> *p_head; ///< pointer to head node

private:

    /**
     * @brief Create node with associated value.
     *
     * @param[in] value: Value.
     *
     * @retval Pointer to new node structure.
     */
    llist_node<T> *node_create(T value)
    {
        llist_node<T> *p_node = NULL;

        p_node = new llist_node<T>;

        p_node->value = value;

        p_node->p_next = NULL;

        return p_node;
    }

    /**
     * @brief Delete node.
     *
     * @param[in,out] p_node: Pointer to node structure.
     */
    void node_delete(llist_node<T> *p_node)
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
    llist_node<T> *node_find(T value)
    {
        llist_node<T> *p_node;

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

    llist_node<T> *p_tail; ///< pointer to tail node

    int num_nodes; ///< number of nodes in list
};

#endif // #ifndef _LLIST_H_
