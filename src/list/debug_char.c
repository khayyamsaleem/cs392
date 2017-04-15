#include "list.h"

void debug_char(struct s_node *head){
    struct s_node *x = head; /* traversal node */
    while(x != NULL) {
        my_char('(');
        print_char(x->prev);
        my_str(" <- ");
        print_char(x);
        my_str(" -> ");
        print_char(x->next);
        my_char(')');

        if (x->next != NULL)
            my_str(", ");
        x = x->next;
    }
}
