#include "list.h"

void debug_int(struct s_node *head){
    struct s_node *x = head; /* traversal node */
    while(x != NULL) {
        my_char('(');
        print_int(x->prev);
        my_str(" <- ");
        print_int(x);
        my_str(" -> ");
        print_int(x->next);
        my_char(')');

        if (x->next != NULL)
            my_str(", ");
        x = x->next;
    }
}
