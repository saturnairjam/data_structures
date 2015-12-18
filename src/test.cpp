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

#define RAND_VALUE_MAX 100 ///< maximum random value

bool strings_are_equal(char *string1, const char *string2);

void test_llist(int num_iterations);
void test_dllist(int num_iterations);

void print_llist(struct llist_node *p_head);
void print_dllist(struct dllist_node *p_node);

char *get_basename(char *path);

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

        printf("Usage: %s [num iterations] [ll|dll]\n", get_basename(argv[0]));

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

                printf("Usage: %s [num iterations] [ll|dll]\n",
                       get_basename(argv[0]));

                retval = EXIT_FAILURE;
            }
        }

        if (retval == EXIT_SUCCESS)
        {
            int num_iterations = atoi(argv[1]);

            if (strings_are_equal(argv[2], "ll"))
            {
                test_llist(num_iterations);
            }
            else if (strings_are_equal(argv[2], "dll"))
            {
                test_dllist(num_iterations);
            }
            else
            {
                printf("!!! error: invalid selection '%s'\n", argv[2]);

                printf("Usage: %s [num iterations] [ll|dll]\n",
                       get_basename(argv[0]));

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

    int rand_value;

    p_llist = new llist;

    srand(time(NULL));

    while (num_iterations--)
    {
        if (rand() % 2)
        {
            rand_value = rand() % (RAND_VALUE_MAX + 1);

            if (rand() % 2)
            {
                printf("add_head(%3d): ", rand_value);

                p_llist->add_head(rand_value);
            }
            else
            {
                printf("add_tail(%3d): ", rand_value);

                p_llist->add_tail(rand_value);
            }

            print_llist(p_llist->p_head);
        }

        if (rand() % 2)
        {
            if (rand() % 2)
            {
                printf("delete_head(): ");

                p_llist->delete_head();
            }
            else
            {
                printf("delete_tail(): ");

                p_llist->delete_tail();
            }

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

    p_dllist = new dllist;

    srand(time(NULL));

    while (num_iterations--)
    {
        if (rand() % 2)
        {
            rand_value = rand() % (RAND_VALUE_MAX + 1);

            if (rand() % 2)
            {
                printf("add_head(%3d): ", rand_value);

                p_dllist->add_head(rand_value);
            }
            else
            {
                printf("add_tail(%3d): ", rand_value);

                p_dllist->add_tail(rand_value);
            }

            print_dllist(p_dllist->p_head);
        }

        if (rand() % 2)
        {
            if (rand() % 2)
            {
                printf("delete_head(): ");

                p_dllist->delete_head();
            }
            else
            {
                printf("delete_tail(): ");

                p_dllist->delete_tail();
            }

            print_dllist(p_dllist->p_head);
        }
    }
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
