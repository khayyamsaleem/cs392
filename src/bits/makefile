CFLAGS = -I../../include -Wall -Werror --pedantic 
SRC = bits.c
OBJS = $(SRC:.c=.o)
LIB = libbits.a
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
