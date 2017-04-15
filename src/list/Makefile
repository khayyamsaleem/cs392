CFLAGS = -I../../include -Wall -Werror --pedantic -std=c99
SRC = add_elem.c add_node.c add_node_at.c append.c count_s_nodes.c debug_char.c debug_int.c debug_string.c elem_at.c empty_list.c new_node.c node_at.c print_char.c print_int.c print_string.c remove_last.c remove_node.c remove_node_at.c traverse_char.c traverse_int.c traverse_string.c 
OBJS = $(SRC:.c=.o)
LIB = liblist.a
CC = gcc

all: $(OBJS)
	ar -rc $(LIB) $(OBJS)
	ranlib $(LIB)
	mv $(LIB) ../../lib

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ../../lib/$(LIB)

re:
	make fclean all

