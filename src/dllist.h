/**
 * @file  dllist.h
 *
 * @brief Doubly-linked list header.
 */

/// doubly-linked list node structure
struct dllist_node {
    int                 value;  ///< node value
    struct dllist_node *p_next; ///< pointer to next node
    struct dllist_node *p_prev; ///< pointer to previous node
};

/// doubly-linked list class
class dllist
{
public:

    dllist();
    ~dllist();

    void add_head(int value);
    void add_tail(int value);

    void delete_head();
    void delete_tail();

    struct dllist_node *p_head; ///< pointer to head node

private:

    struct dllist_node * node_create(int value);

    void node_delete(struct dllist_node *p_node);

    struct dllist_node *p_tail; ///< pointer to tail node

    int num_nodes; ///< number of nodes in list
};
