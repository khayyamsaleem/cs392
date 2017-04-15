#include "list.h"

void traverse_string(struct s_node *head){
    struct s_node *x = head; /* traversal node */
    while(x != NULL) {
        print_string(x);
        my_char(' ');
        x = x->next;
    }
}
