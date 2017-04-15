#include "list.h"

void *remove_node_at(struct s_node **head, int n){
    struct s_node **loc = head;
    if (head == NULL || *head == NULL)
        return NULL;


    while ((*loc)->next != NULL && n > 0) {
        --n;
        loc = &(*loc)->next;
    }

    return remove_node(loc);
}
