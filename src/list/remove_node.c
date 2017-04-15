#include "list.h"

void *remove_node(struct s_node **node){
    /*create a copy of the node so we don't overwrite it*/
    struct s_node *copy = NULL;
    void *elem = NULL; /* element itself (copy)*/
    struct s_node *next = NULL;

    if (node == NULL || *node == NULL){
        free(copy);
        free(elem);
        free(next);
        return NULL;
    }

    copy = *node;
    if (copy->prev != NULL)
        copy->prev->next = copy->next;
    if (copy->next != NULL)
        copy->next->prev = copy->prev;

    elem = copy->elem;
    next = copy->next;
    /*if list is empty */
    if (copy->prev == NULL && copy->next == NULL) {
        free(copy);
        *node = NULL;
    } else if (copy->prev == NULL) { /*remove head*/
        next = copy->next;
        free(copy);
        *node = next;
    } else {
        free(copy);
    }

    return elem;
}
