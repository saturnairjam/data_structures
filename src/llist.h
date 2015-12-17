/**
 * @file  llist.h
 *
 * @brief Linked list header.
 */

/// node structure
struct node {
    int          value;  ///< node value
    struct node *p_next; ///< pointer to next node
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

    struct node *p_head; ///< pointer to head node

private:

    struct node * node_create(int value);

    void node_delete(struct node *p_node);

    struct node *p_tail; ///< pointer to tail node

    int num_nodes; ///< number of nodes
};
