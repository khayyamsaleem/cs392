#include "list.h"

void print_char(struct s_node *node)
{

    if (node == NULL)
        my_str("NULL");
    else if (node->elem == NULL)
        my_str("(null elem)");
    else
        my_char(*(char *)node->elem);
}
