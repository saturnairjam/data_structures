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

#define RAND_VALUE_MAX 100 ///< maximum random value

void print_list(struct node *p_head);

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
    llist *p_llist;

    int num_iterations;

    int rand_value;

    if (argc != 2)
    {
        printf("Usage: %s [num iterations]\n", get_basename(argv[0]));

        return EXIT_FAILURE;
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

                return EXIT_FAILURE;
            }
        }

        num_iterations = atoi(argv[1]);
    }

    srand(time(NULL));

    p_llist = new llist;

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

            print_list(p_llist->p_head);
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

            print_list(p_llist->p_head);
        }
    }

    delete p_llist;

    return EXIT_SUCCESS;
}

/**
 * @brief Print list.
 *
 * @param[in] p_node: Pointer to node structure.
 */
void print_list(struct node *p_node)
{
    while (p_node != NULL)
    {
        printf("%4d -> ", p_node->value);

        p_node = p_node->p_next;
    }

    printf("NULL\n");
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
