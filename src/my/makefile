CFLAGS = -I../../include -Wall -Werror --pedantic 
SRC = my_alpha.c my_char.c my_str.c my_strlen.c my_revstr.c
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
