#include "list.h"

void traverse_char(struct s_node *head){
    struct s_node *x = head;
    while(x != NULL) {
        print_char(x);
        my_char(' ');
        x = x->next;
    }
}
