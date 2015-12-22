/**
 * @file  test.cpp
 *
 * @brief Test source.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "llist.h"
#include "dllist.h"
#include "stack.h"
#include "queue.h"

#define RAND_VALUE_MAX 100 ///< maximum random value

bool strings_are_equal(char *string1, const char *string2);

void test_llist(int num_iterations);
void test_dllist(int num_iterations);
void test_stack(int num_iterations);
void test_queue(int num_iterations);

void print_llist(struct llist_node *p_head);
void print_dllist(struct dllist_node *p_node);

char *get_basename(char *path);

/**
 * @brief Print usage string.
 */
void print_usage(char **argv)
{
    printf("Usage: %s [num iterations] [llist|dllist|stack|queue]\n",
           get_basename(argv[0]));
}

/**
 * @brief Main function.
 *
 * @param[in] argc: Number of command-line arguments.
 * @param[in] argv: Array of command-line argument strings.
 *
 */
int main(int argc, char **argv)
{
    int retval = EXIT_SUCCESS;

    if (argc != 3)
    {
        printf("!!! error: not enough command-line arguments\n");

        print_usage(argv);

        retval = EXIT_FAILURE;
    }
    else
    {
        int ii;

        for (ii = 0; argv[1][ii] != '\0'; ii++)
        {
            if (!isdigit(argv[1][ii]))
            {
                printf("!!! error: invalid number of iterations '%s'\n",
                       argv[1]);

                print_usage(argv);

                retval = EXIT_FAILURE;
            }
        }

        if (retval == EXIT_SUCCESS)
        {
            int num_iterations = atoi(argv[1]);

            if (strings_are_equal(argv[2], "llist"))
            {
                test_llist(num_iterations);
            }
            else if (strings_are_equal(argv[2], "dllist"))
            {
                test_dllist(num_iterations);
            }
            else if (strings_are_equal(argv[2], "stack"))
            {
                test_stack(num_iterations);
            }
            else if (strings_are_equal(argv[2], "queue"))
            {
                test_queue(num_iterations);
            }
            else
            {
                printf("!!! error: invalid selection '%s'\n", argv[2]);

                print_usage(argv);

                retval = EXIT_FAILURE;
            }
        }
    }

    return retval;
}

/**
 * @brief Test linked list.
 *
 * @param[in] num_iterations: Number of iterations.
 */
void test_llist(int num_iterations)
{
    llist *p_llist;

    int rand_value, rand_index;

    int num_nodes = 0;

    p_llist = new llist;

    srand(time(NULL));

    while (num_iterations--)
    {
        if (rand() % 2)
        {
            rand_value = rand() % (RAND_VALUE_MAX + 1);

            if (rand() % 2)
            {
                printf("     add_head(): %3d: ", rand_value);

                p_llist->add_head(rand_value);
            }
            else
            {
                printf("     add_tail(): %3d: ", rand_value);

                p_llist->add_tail(rand_value);
            }

            num_nodes++;

            print_llist(p_llist->p_head);
        }

        if (num_nodes && (rand() % 2))
        {
            struct llist_node *p_node;

            rand_index = rand() % num_nodes;

            rand_value = rand() % (RAND_VALUE_MAX + 1);

            printf("add_before(%3d): %3d: ", rand_index, rand_value);

            p_node = p_llist->p_head;

            while (rand_index--)
            {
                p_node = p_node->p_next;
            }

            p_llist->add_before(p_node, rand_value);

            num_nodes++;

            print_llist(p_llist->p_head);
        }

        if (num_nodes && (rand() % 2))
        {
            struct llist_node *p_node = p_llist->p_head;

            int rand_index = rand() % num_nodes;

            while (rand_index--)
            {
                p_node = p_node->p_next;
            }

            printf("       remove(): %3d: ", p_node->value);

            p_llist->remove(p_node->value);

            num_nodes--;

            print_llist(p_llist->p_head);
        }

        if (num_nodes && rand() % 2)
        {
            if (rand() % 2)
            {
                printf("  delete_head():      ");

                p_llist->delete_head();
            }
            else
            {
                printf("  delete_tail():      ");

                p_llist->delete_tail();
            }

            num_nodes--;

            print_llist(p_llist->p_head);
        }
    }

    delete p_llist;
}

/**
 * @brief Test doubly-linked list.
 *
 * @param[in] num_iterations: Number of iterations.
 */
void test_dllist(int num_iterations)
{
    dllist *p_dllist;

    int rand_value;

    int num_nodes = 0;

    p_dllist = new dllist;

    srand(time(NULL));

    while (num_iterations--)
    {
        if (rand() % 2)
        {
            rand_value = rand() % (RAND_VALUE_MAX + 1);

            if (rand() % 2)
            {
                printf("   add_head(): %3d: ", rand_value);

                p_dllist->add_head(rand_value);
            }
            else
            {
                printf("   add_tail(): %3d: ", rand_value);

                p_dllist->add_tail(rand_value);
            }

            num_nodes++;

            print_dllist(p_dllist->p_head);
        }

        if (num_nodes && (rand() % 2))
        {
            struct dllist_node *p_node = p_dllist->p_head;

            int rand_index = rand() % num_nodes;

            while (rand_index--)
            {
                p_node = p_node->p_next;
            }

            printf("     remove(): %3d: ", p_node->value);

            p_dllist->remove(p_node->value);

            num_nodes--;

            print_dllist(p_dllist->p_head);
        }

        if (num_nodes && (rand() % 2))
        {
            if (rand() % 2)
            {
                printf("delete_head():      ");

                p_dllist->delete_head();
            }
            else
            {
                printf("delete_tail():      ");

                p_dllist->delete_tail();
            }

            num_nodes--;

            print_dllist(p_dllist->p_head);
        }
    }
}

/**
 * @brief Test stack.
 *
 * @param[in] num_iterations: Number of iterations.
 */
void test_stack(int num_iterations)
{
    stack *p_stack;

    int rand_value;

    int num_items = 0;

    p_stack = new stack;

    srand(time(NULL));

    while (num_iterations--)
    {
        if (rand() % 2)
        {
            rand_value = rand() % (RAND_VALUE_MAX + 1);

            printf("push(): %3d: ", rand_value);

            p_stack->push(rand_value);

            num_items++;

            print_llist(p_stack->p_llist->p_head);
        }

        if (num_items && (rand() % 2))
        {
            printf(" pop(): %3d: ", p_stack->pop());

            num_items--;

            print_llist(p_stack->p_llist->p_head);
        }

        if (num_items && (rand() % 2))
        {
            printf("peek(): %3d: ", p_stack->peek());

            print_llist(p_stack->p_llist->p_head);
        }
    }

    delete p_stack;
}

/**
 * @brief Test queue.
 *
 * @param[in] num_iterations: Number of iterations.
 */
void test_queue(int num_iterations)
{
    queue *p_queue;

    int rand_value;

    int num_items = 0;

    p_queue = new queue;

    srand(time(NULL));

    while (num_iterations--)
    {
        if (rand() % 2)
        {
            rand_value = rand() % (RAND_VALUE_MAX + 1);

            printf("enqueue(): %3d: ", rand_value);

            p_queue->enqueue(rand_value);

            num_items++;

            print_llist(p_queue->p_llist->p_head);
        }

        if (num_items && (rand() % 2))
        {
            printf("dequeue(): %3d: ", p_queue->dequeue());

            num_items--;

            print_llist(p_queue->p_llist->p_head);
        }
    }

    delete p_queue;
}

/**
 * @brief Print linked list.
 *
 * @param[in] p_node: Pointer to node structure.
 */
void print_llist(struct llist_node *p_node)
{
    while (p_node != NULL)
    {
        printf("%4d -> ", p_node->value);

        p_node = p_node->p_next;
    }

    printf("NULL\n");
}

/**
 * @brief Print doubly-linked list.
 *
 * @param[in] p_node: Pointer to node structure.
 */
void print_dllist(struct dllist_node *p_node)
{
    if (p_node == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("NULL <-- ");

        while (p_node != NULL)
        {
            printf("%4d <-> ", p_node->value);

            p_node = p_node->p_next;
        }

        printf("\b\b\b\b\b --> NULL\n");
    }
}

/**
 * @brief Get basename from string containing file + full path.
 *
 * @param[in] path: File + full path string.
 *
 * @retval Basename string.
 */
char *get_basename(char *path)
{
    char *basename;

    basename = strrchr(path, '/');

    if (basename == NULL)
    {
        basename = strrchr(path, '\\');

        if (basename == NULL)
        {
            basename = path;
        }
        else
        {
            basename++;
        }
    }
    else
    {
        basename++;
    }

    return basename;
}

/**
 * @brief Check if two sets of strings are equal.
 *
 * @param[in] string1: String 1.
 * @param[in] string2: String 2.
 *
 * @retval  true if string 1 == string 2
 * @retval false if string 1 != string 2
 */
bool strings_are_equal(char *string1, const char *string2)
{
    if ((strlen(string1) == strlen(string2)) &&
        (strncmp(string1, string2, strlen(string1)) == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}
