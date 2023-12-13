#include <stdio.h>

struct {
    char x;
    void* ptr;
} Foo;

int main(){

    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(void*) = %zu\n", sizeof(void*));
    printf("sizeof(Foo) = %zu\n", sizeof(Foo));//There is padding on the struct to make the memory align properly. WOW!

    return 0;
}