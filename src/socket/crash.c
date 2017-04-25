#include <stdio.h>
int main() {
    gone();
    printf("my crash didn't work");
}
int gone() {
    char a[2];
    a[2] = 'x';
}
