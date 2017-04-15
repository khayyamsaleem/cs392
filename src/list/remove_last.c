#include "list.h"

void *remove_last(struct s_node **head){
    struct s_node **last = head; 

    if (head == NULL || *head == NULL)
        return NULL;

    while ((*last)->next != NULL)
        last = &(*last)->next;

    return remove_node(last);
}
