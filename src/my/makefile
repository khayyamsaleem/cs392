CFLAGS = -I../../include -Wall -Werror --pedantic -std=c99
SRC = my_alpha.c my_char.c my_str.c my_strlen.c my_revstr.c my_int.c my_num_base.c my_strindex.c my_strrindex.c my_strfind.c my_strrfind.c my_strcmp.c my_strncmp.c my_strcpy.c my_strncpy.c my_strcat.c my_strdup.c my_strconcat.c my_strnconcat.c my_atoi.c
OBJS = $(SRC:.c=.o)
LIB = libmy.a
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
