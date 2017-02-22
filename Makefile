CFLAGS += -I ./include -g -std=c99 -Wall -Werror -pedantic

MY_SRC := \
	  src/my/my_alpha.c \
	  src/my/my_char.c \
	  src/my/my_revstr.c \
	  src/my/my_str.c \
	  src/my/my_strlen.c \
	  src/my/my_int.c

MY_OBJ := $(MY_SRC:.c=.o)

MY_LIB := lib/libmy.a

TESTS := \
	test/testmy \
	test/testbits \
	test/test_myint 

all: \
	$(MY_LIB) \
	$(TESTS) 

clean:
	$(RM) $(MY_OBJ)
	$(RM) $(TESTS) 
	$(RM) src/bits/bits.o

fclean: clean
	$(RM) $(MY_LIB)
	$(RM) $(TESTS)

re: fclean all

check: $(TESTS)
	$(TESTS)

.PHONY: all clean fclean re check

test/testmy: $(MY_LIB)

test/testbits: $(MY_LIB) src/bits/bits.c

test/test_myint: $(MY_LIB)

$(MY_LIB): $(MY_OBJ)

%.a:
	$(AR) rcs $@ $^
