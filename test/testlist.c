#define _POSIX_SOURCE
#include "list.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define UNUSED(x) ((x) = (x))

#define assert(p)                                                              \
    ((p) ? my_str("\x1B[32m✓\x1B[0m " #p "\n")                                 \
     : assert_failed(#p, __FILE__, __LINE__))

void assert_failed(char *p, char *file, int line){
    my_str(file);
    my_char(':');
    my_int(line);
    my_str(": Assertion `");
    my_str(p);
    my_str("' failed\n");
    kill(getpid(), SIGABRT); /* suicide */
}

void note(char *s){
    my_str("\x1B[33m");
    my_str(s);
    my_str("\x1B[0m");
}

int *mkint(int i){
    int *p = malloc(sizeof(int));
    *p = i;
    return p;
}

int main(){
    struct s_node *head;
    struct s_node *null_head = NULL;
    struct s_node *nn = new_node("hey");
    struct s_node *s = new_node(NULL);
    struct s_node *null_node = new_node(NULL);
    struct s_node *next = NULL;
    void *nullelem = NULL;
    int *elem = NULL;
    char *str = "helloworld";
    struct s_node *node_L = new_node(&str[3]);
    struct s_node *badnode = new_node("bad node");
    int *one = mkint(1), *two = mkint(2), *three = mkint(3);
    char *badelem = NULL;
    char *l_elem = NULL;
    struct s_node *a = NULL, *b = NULL;
    struct s_node *new_b = NULL;

    my_str("\n\n\n");


    note("NULL checks\n");
    head = new_node(NULL);
    add_node(NULL, &head);
    assert(head->next == NULL && head->prev == NULL);
    /*    my_str("made it\n"); */
    /*    my_str("made it\n"); */
    add_node(nn, NULL);
    /*    my_str("made it\n"); */
    assert(nn->prev == NULL && nn->next == NULL);
    add_node(nn, &null_head);
    debug_string(null_head);
    my_char('\n');
    assert(my_strcmp(elem_at(null_head, 0), "hey") == 0);
    empty_list(&null_head);
    assert(null_head == NULL);
    add_node(s, &head);
    assert(count_s_nodes(head) == 1);
    remove_node(&s);
    assert(s == NULL);
    add_elem(NULL, &head);
    assert(count_s_nodes(head) == 1);
    /*    my_str("made it\n"); */
    assert(head->next == NULL && head->prev == NULL);
    append(NULL, &head);
    assert(head->next == NULL && head->prev == NULL);
    s = new_node("hi");
    null_head = NULL;
    append(s, &null_head);
    assert(null_head != NULL);
    assert(my_strcmp(null_head->elem, "hi") == 0);
    empty_list(&null_head);
    s = new_node(NULL);
    append(s, &head);
    remove_node(&s);
    /*    my_str("made it\n");*/
    assert(head->next == NULL && head->prev == NULL);
    add_node_at(NULL, &head, 0);
    assert(head->next == NULL && head->prev == NULL);
    s = new_node("ok");
    add_node_at(s, &null_head, 0);
    assert(my_strcmp(null_head->elem, "ok") == 0);
    empty_list(&null_head);
    s = new_node(NULL);
    add_node_at(s, &head, 0);
    /*    my_str("made it\n"); */
    nullelem = remove_node(&s);
    assert(nullelem == NULL);
    assert(head->next == NULL && head->prev == NULL);
    /*    my_str("made it\n"); */
    assert(remove_node(NULL) == NULL);
    assert(remove_node(&null_head) == NULL);
    assert(remove_last(NULL) == NULL);
    assert(remove_last(&null_head) == NULL);
    assert(remove_node_at(NULL, 109238) == NULL);
    assert(remove_node_at(&null_head, 109238) == NULL);
    s = new_node("ok");
    add_node_at(s, &head, -20);
    assert(s->prev == NULL && s->next == NULL);
    remove_node(&s);

    traverse_int(head);
    debug_int(head);
    empty_list(&head);
    my_char('\n');

    empty_list(NULL);
    assert(node_at(NULL, 42) == NULL);
    assert(elem_at(NULL, 42) == NULL);
    assert(count_s_nodes(NULL) == 0);
    empty_list(NULL);

    my_str("\n-------\n");

    head = new_node(three);
    traverse_int(head);
    debug_int(head);
    my_char('\n');
    assert(remove_node(&head) == three);
    assert(head == NULL);

    my_str("-------\n");

    head = new_node(one);
    add_elem(two, &head);
    assert(node_at(head, -20) == head);
    note("added 1, 2\n");
    assert(*(int *)head->elem == 2);
    traverse_int(head);
    debug_int(head);

    remove_node(&head);
    note("\nremoved head, now we have: ");
    debug_int(head);

    remove_node(&head);
    note("\nremoved head, now we have: ");
    debug_int(head);
    my_char('\n');

    assert(head == NULL);

    my_str("-------\n");

    head = new_node(one);
    add_elem(two, &head);
    note("added 1, 2\n");
    assert(*(int *)head->elem == 2);
    traverse_int(head);
    debug_int(head);

    remove_last(&head);
    note("\nremoved last, now we have: ");
    debug_int(head);

    remove_last(&head);
    note("\nremoved last, now we have: ");
    debug_int(head);
    my_char('\n');

    assert(head == NULL);

    my_str("-------\n");

    head = new_node(one);
    add_elem(two, &head);
    add_elem(three, &head);
    note("added 1, 2, 3\n");
    assert(*(int *)head->elem == 3);
    traverse_int(head);
    debug_int(head);

    elem = remove_node_at(&head, 1);
    my_char('\n');
    assert(*elem == 2);
    note("\nremoved list[1], now we have: ");
    debug_int(head);

    elem = remove_node_at(&head, 0);
    my_char('\n');
    assert(*elem == 3);
    note("\nremoved list[0], now we have: ");
    debug_int(head);
    my_char('\n');

    elem = remove_last(&head);
    assert(*elem == 1);

    assert(head == NULL);

    empty_list(&head);

    my_str("-------\n");

    head = new_node(one);
    add_elem(two, &head);
    add_elem(three, &head);
    note("added 1, 2, 3\n");
    assert(*(int *)head->elem == 3);
    traverse_int(head);
    debug_int(head);

    empty_list(&head);
    note("\ndeleted list: ");
    debug_int(head);

    my_str("\n-------\n");

    head = new_node("head");
    add_elem("new-head", &head);
    append(new_node("new-tail"), &head);
    assert(my_strcmp(head->elem, "new-head") == 0);
    traverse_string(head);
    my_char('\n');
    add_node_at(new_node("index-0"), &head, 0);
    add_node_at(new_node("index-1"), &head, 1);
    add_node_at(new_node("last-node"), &head, 99);
    add_node_at(new_node("index-3"), &head, 3);
    add_node_at(NULL, &head, 2);
    add_node_at(null_node, &head, 2);
    remove_node(&null_node);
    traverse_string(head);
    debug_string(head);
    empty_list(&head);

    my_str("\n-------\n");

    note("checking that add_node_at can add before last node AND after all "
            "nodes\n");
    head = new_node("4");
    add_elem("3", &head);
    add_elem("2", &head);
    add_elem("1", &head);
    add_elem("0", &head);
    traverse_string(head);
    my_char('\n');
    add_node_at(new_node("inserted-in-pos-3"), &head, 3);
    assert(my_strcmp(elem_at(head, 3), "inserted-in-pos-3") == 0);
    traverse_string(head);
    my_char('\n');
    remove_node_at(&head, 3);
    traverse_string(head);
    my_char('\n');
    add_node_at(new_node("inserted-in-pos-4"), &head, 4);
    assert(my_strcmp(elem_at(head, 4), "inserted-in-pos-4") == 0);
    traverse_string(head);
    my_char('\n');
    remove_node_at(&head, 4);
    add_node_at(new_node("tail"), &head, 99);
    traverse_string(head);

    empty_list(&head);

    my_str("\n-------\n");

    head = new_node("head");
    add_elem("new-head", &head);
    next = node_at(head, 1);
    append(new_node("new-tail"), &head);
    traverse_string(head);
    my_char('\n');
    remove_node(&head);
    assert(head == next);
    empty_list(&head);

    my_str("\n-------\n");

    head = new_node(&str[2]);
    assert(head->elem == &str[2]);
    assert(head->next == NULL);
    assert(head->prev == NULL);
    assert(count_s_nodes(head) == 1);
    add_elem(&str[1], &head);
    assert(count_s_nodes(head) == 2);
    add_elem(&str[0], &head);
    assert(count_s_nodes(head) == 3);
    append(node_L, &head);
    assert(count_s_nodes(head) == 4);
    append(new_node(&str[4]), &head);
    assert(count_s_nodes(head) == 5);
    append(new_node(&str[5]), &head);
    assert(count_s_nodes(head) == 6);
    add_node_at(badnode, &head, 3);
    assert(count_s_nodes(head) == 7);
    badelem = remove_node(&badnode);
    assert(my_strcmp(badelem, "bad node") == 0);
    assert(count_s_nodes(head) == 6);
    traverse_char(head);
    debug_char(head);
    my_char('\n');
    l_elem = remove_last(&head);
    assert(*l_elem == 'w');
    assert(count_s_nodes(head) == 5);
    traverse_char(head);
    my_char('\n');
    l_elem = remove_node_at(&head, 1);
    assert(count_s_nodes(head) == 4);
    my_char('\n');
    debug_char(head);
    my_char('\n');
    assert(node_at(head, 2) == node_L);
    assert(*(char *)node_L->elem == 'l');
    assert(elem_at(head, 2) == node_L->elem);
    empty_list(&head);
    assert(count_s_nodes(head) == 0);

    my_str("\n-------\n");

    /**
     * Adding a list to add_node or add_node_at should add just the single node
     * Adding a list with append should add the node and all following
     */

    a = new_node("a1");
    append(new_node("a2"), &a);
    append(new_node("a3"), &a);
    note("list a: ");
    traverse_string(a);
    my_char('\n');

    b = new_node("b1");
    append(new_node("b2"), &b);
    append(new_node("b3"), &b);
    note("list b: ");
    traverse_string(b);
    my_char('\n');

    note("add_node b to a\n");
    new_b = b->next;
    add_node(b, &a);
    b = new_b;
    note("a: ");
    traverse_string(a);
    my_char('\n');
    assert(count_s_nodes(a) == 4);
    note("b: ");
    traverse_string(b);
    my_char('\n');
    assert(count_s_nodes(b) == 2);

    note("add_node_at b to a\n");
    add_node_at(b->next, &a, 3);
    note("a: ");
    traverse_string(a);
    my_char('\n');
    assert(count_s_nodes(a) == 5);
    note("b: ");
    traverse_string(b);
    my_char('\n');
    assert(count_s_nodes(b) == 1);

    note("add node a[1] to list a\n");
    note("a: ");
    traverse_string(a);
    my_char('\n');
    add_node(a->next, &a);
    note("a: ");
    traverse_string(a);
    my_char('\n');

    my_char('\n');

    /* make sure nothing changed these */
    assert(*one == 1);
    assert(*two == 2);
    assert(*three == 3);
    free(one);
    free(two);
    free(three);

    my_str("\n\n\n");
    return 0;
}
