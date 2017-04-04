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
	  src/my/my_atoi.c 

SIGNALS := \
	  src/signals/signals.c


MY_OBJ := $(MY_SRC:.c=.o) \
	  $(SIGNALS:.c=.o)

MY_LIB := lib/libmy.a

TESTS := \
	test/testmy \
	test/testbits \
	test/test_myint 

all: \
	$(MY_LIB) \
	$(TESTS) \
	$(SIGNALS)

clean:
	$(RM) $(MY_OBJ)
	$(RM) $(TESTS) 
	$(RM) src/bits/bits.o
	$(RM) -r test/*.dSYM
	$(RM) -r src/my/*.dSYM

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
	$(RM) $@
	$(AR) rcs $@ $^
