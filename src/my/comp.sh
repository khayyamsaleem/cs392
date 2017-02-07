gcc -c *.c -Wall -Werror --pedantic -I../../include
ar -rc libmy.a *.o
ranlib libmy.a
mv libmy.a ../../lib
