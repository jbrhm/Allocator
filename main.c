#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAPACITY 640000

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

void* heap_alloc(size_t size){
    assert(heap_size + size <= HEAP_CAPACITY);

    void* result = heap + heap_size;
    heap_size += size;

    return result;
}

void heap_free(void* ptr){

}

void heap_collect(){

}


int main(){
    printf("This should be the number three %d \n", 3);

    char* root = heap_alloc(26);
    for(int i = 0; i < 26; i++){
        root[i] = i + 'A';
    }

    for(int i = 0; i < 26; i++){
        printf("%c \n", root[i]);
    }
    
    return 0;
}