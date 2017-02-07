  #include <stdio.h> 
  #include "my.h"
  int main(){ 
	
  char a[] = "a";
  char ab[] = "ab";
  char abc[] = "abc";
  
  my_str(""); /*prints nothing*/
  my_str(NULL); /*prints nothing*/
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
}
