OBJS = server.o client.o
EXECS = server client
CFLAGS = -Wall -Werror --pedantic -I../../include
LFLAGS = -L../../lib -lmy -llist
NAMES = libmy.a liblist.a
CC = gcc -std=c99

all: $(OBJS)
	$(CC) client.c -o client $(CFLAGS) $(LFLAGS) -g -lncurses
	$(CC) server.c -o server $(CFLAGS) $(LFLAGS) -g

clean:
	rm -f $(OBJS)

fclean: clean
	rm $(EXECS)

re:
	make fclean all