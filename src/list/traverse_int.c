#include "list.h"

void traverse_int(struct s_node *head){
    struct s_node *x = head; /* traversal node */
    while(x != NULL) {
        print_int(x);
        my_char(' ');
        x = x->next;
    }
}
