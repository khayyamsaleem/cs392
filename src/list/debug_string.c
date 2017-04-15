#include "list.h"

void debug_string(struct s_node *head){
    struct s_node *x = head; /* traversal node */
    while(x != NULL){
        my_char('(');
        print_string(x->prev);
        my_str(" <- ");
        print_string(x);
        my_str(" -> ");
        print_string(x->next);
        my_char(')');

        if (x->next != NULL)
            my_str(", ");
        x = x->next;
    }
}
