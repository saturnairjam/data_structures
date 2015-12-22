/**
 * @file  llist.h
 *
 * @brief Linked list header.
 */

#ifndef _LLIST_H_

#define _LLIST_H_

/// linked list node structure
struct llist_node {
    int                value;  ///< node value
    struct llist_node *p_next; ///< pointer to next node
};

/// linked list class
class llist
{
public:

    llist();
    ~llist();

    void add_head(int value);
    void add_tail(int value);

    void delete_head();
    void delete_tail();

    void remove(int value);

    void add_before(struct llist_node *p_node, int value);

    struct llist_node *p_head; ///< pointer to head node

private:

    struct llist_node * node_create(int value);
    void                node_delete(struct llist_node *p_node);
    struct llist_node * node_find(int value);

    struct llist_node *p_tail; ///< pointer to tail node

    int num_nodes; ///< number of nodes in list
};

#endif // #ifndef _LLIST_H_
