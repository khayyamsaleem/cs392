CFLAGS += -I ./include -g -Wall -Werror -pedantic -std=c99

MY_SRC := \
    src/my/my_alpha.c \
    src/my/my_char.c \
    src/my/my_revstr.c \
    src/my/my_str.c \
    src/my/my_strlen.c \
    src/my/my_int.c \
    src/my/my_num_base.c \
    src/my/my_strindex.c \
    src/my/my_strrindex.c \
    src/my/my_strfind.c \
    src/my/my_strrfind.c \
    src/my/my_strcmp.c \
    src/my/my_strncmp.c \
    src/my/my_strcpy.c \
    src/my/my_strncpy.c \
    src/my/my_strcat.c \
    src/my/my_strdup.c \
    src/my/my_strconcat.c \
    src/my/my_strnconcat.c \
    src/my/my_atoi.c \
    src/my/my_vect2str.c

SIGNALS := \
    src/signals/signals.c

PIPES := \
    src/pipes/pipes.c

SOCKET := \
    src/socket/client.c


MY_OBJ := $(MY_SRC:.c=.o) \
    $(SIGNALS:.c=.o) \
    $(PIPES:.c=.o) \
    $(SOCKET:.c=.o)

MY_LIB := lib/libmy.a

LIST_SRC := \
    src/list/add_elem.c \
    src/list/add_node.c \
    src/list/add_node_at.c \
    src/list/append.c \
    src/list/count_s_nodes.c \
    src/list/debug_char.c	\
    src/list/debug_int.c \
    src/list/debug_string.c \
    src/list/elem_at.c \
    src/list/empty_list.c \
    src/list/new_node.c \
    src/list/node_at.c \
    src/list/print_char.c \
    src/list/print_int.c \
    src/list/print_string.c \
    src/list/remove_last.c \
    src/list/remove_node.c \
    src/list/remove_node_at.c \
    src/list/traverse_char.c \
    src/list/traverse_int.c \
    src/list/traverse_string.c

LIST_OUT := $(LIST_SRC:.c=.o)

LIST_LIB := lib/liblist.a

PIPES_BIN := src/pipes/pipes

SOCKET_BIN := src/socket/client

SOCKETTALK_BIN := \
    src/sockettalk/server \
    src/sockettalk/client

TESTS := \
    test/testmy \
    test/testbits \
    test/test_myint \
    test/testlist

all: \
    $(MY_LIB) \
    $(LIST_LIB) \
    $(TESTS) \
    $(SIGNALS) \
    $(PIPES_BIN) \
    $(SOCKET_BIN) \
    $(SOCKETTALK_BIN)

clean:
	$(RM) $(MY_OBJ)
	$(RM) $(LIST_OUT)
	$(RM) $(PIPES_BIN)
	$(RM) src/bits/bits.o
	$(RM) -r test/*.dSYM
	$(RM) -r src/my/*.dSYM
	$(RM) $(SOCKET_BIN)
	$(RM) $(SOCKETTALK_BIN)

fclean: clean
	$(RM) $(MY_LIB)
	$(RM) $(LIST_LIB)
	$(RM) $(TESTS)

re: fclean all

check: $(TESTS)
	test/testmy
	test/testbits
	test/testlist

.PHONY: all clean fclean re check

test/testmy: $(MY_LIB)

test/testbits: $(MY_LIB) src/bits/bits.c

test/test_myint: $(MY_LIB)

test/testlist: $(MY_LIB) $(LIST_LIB)

$(MY_LIB): $(MY_OBJ)

$(LIST_LIB): $(LIST_OUT)

$(PIPES_BIN): $(MY_LIB)

$(SOCKETTALK_BIN): $(MY_LIB) $(LIST_LIB) 

$(SOCKETTALK_BIN): LDLIBS += $(shell pkg-config --libs ncurses)

%.a:
	$(RM) $@
	$(AR) rcs $@ $^
