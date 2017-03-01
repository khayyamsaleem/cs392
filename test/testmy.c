#include <stdio.h> 
#include "my.h"
int main(){ 

    /* Testing first half of string library
       char a[] = "a"; char ab[] = "ab";
       char abc[] = "abc";

       my_str(""); //prints nothing
       my_str(NULL); //prints nothing
       my_str("Hello");
       my_str(" World!\n");
       my_char('\n');
       printf("%i\n", my_strlen(a)); 
       printf("%i\n", my_strlen(""));
       printf("%i\n", my_strlen(NULL));
       printf("%i\n", my_strlen(ab));
       printf("%i\n", my_strlen(abc));
       my_str(a);
       printf(" %i\n", my_revstr(a));
       my_str(ab);
       printf(" %i\n", my_revstr(ab));
       my_str(abc);
       printf(" %i\n", my_revstr(abc));
       printf(" %i\n", my_revstr(NULL)); 
       my_alpha();
       return 0;
       */

    /* 
     * Testing my_int
     my_int(0);
     my_char('\n');
     my_int(10);
     my_char('\n');
     my_int(3245);
     my_char('\n');
     my_int(101);
     my_char('\n');
     my_int(-1);
     my_char('\n');
     my_int(-34);
     my_char('\n');
     my_int(-10);
     my_char('\n');
     my_int(1);
     my_char('\n');
     my_int(10000);
     my_char('\n');
     my_int(2147483647);
     my_char('\n');
     my_int(-2147483648);
     my_char('\n');
     my_int(1200000);
     my_char('\n');
     my_int(1200001);
     my_char('\n');
     return 0;
     */

    /* Testing 2nd half of string library */
    my_str("Testing my_num_base, (9, 'RTFM') -> FT\n");
    my_num_base(9, "RTFM");
    my_char('\n');
    my_str("Testing my_strindex, ('cheese', 's') -> 4\n");
    my_int(my_strindex("cheese", 's'));
    my_char('\n');
    my_str("Testing my_strindex, ('cheese', 'w') -> -1\n");
    my_int(my_strindex("cheese", 'w'));
    my_char('\n');
    my_str("Testing my_strrindex, ('cheese', 'e') -> 5\n");
    my_int(my_strrindex("cheese", 'e'));
    my_char('\n');
    my_str("Testing my_strfind, ('cheese', 's') -> ptr\nthat when dereferenced, yields 's'\n");
    my_char(*my_strfind("cheese", 's'));
    my_char('\n');
    my_str("Testing my_strrfind, ('cheese', 'e') -> ptr\nthat when dereferenced, yields 'e'\n");
    my_char(*my_strrfind("cheese", 'e'));
    my_char('\n');
    my_str("Testing my_strcmp, ('cheese', 'cheese') -> 0\n");
    my_int(my_strcmp("cheese", "cheese"));
    my_char('\n');
    my_str("Testing my_strcmp, ('cheese', 'chomp') -> -10\n");
    my_int(my_strcmp("cheese", "chomp"));
    my_char('\n');
    my_str("Testing my_strncmp, ('cheese', 'chomp', 2) -> 0\n");
    my_int(my_strncmp("cheese", "chomp", 2));
    my_char('\n');
    my_str("Testing my_atoi, ('a-b-54sc85-ed') -> 54\n");
    my_int(my_atoi("a-b-54sc85-ed"));
    my_char('\n');
    return 0;

}
