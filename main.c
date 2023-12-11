#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAPACITY 640000
#define HEAP_ALLOCED_CAPACITY 640000
#define HEAP_FREED_CAPACITY 640000


typedef struct
{
    void* ptr;
    size_t size;
}  Heap_Chunk;


char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

Heap_Chunk heap_alloced[HEAP_ALLOCED_CAPACITY] = {0};
size_t heap_alloced_size = 0;

Heap_Chunk heap_freed[HEAP_FREED_CAPACITY] = {0};
size_t heap_freed_size = 0;

void* heap_alloc(size_t size){

    //IF THE SIZE OF THE ALLOCATED CHUNK IS 0 RETURN NULL SO ALL OF THE POINTERS RETURNED ARE EITHER UNIQUE OR NULL
    if(size == 0){
        return NULL;
    }

    //ASSERT THE ALLOCATED MEMORY IS WITHIN THE HEAP CAPACITY
    assert(heap_size + size <= HEAP_CAPACITY);

    //GET THE HEAP PTR POINTING TO THE NEW ALLOCATED DATA
    void* result = heap + heap_size;

    //UPDATE THE HEAP SIZE
    heap_size += size;

    //CREATE THE CHUNK TO BE ALLOCATED
    const Heap_Chunk chunk = {
        .ptr = result,
        .size = size
    };

    //ASSERT THE ALLOCATED MEMORY IS WITHIN THE CHUNK CAPACITY
    assert(heap_alloced_size < HEAP_ALLOCED_CAPACITY);
    //PLACE THE CHUNK INTO THE CHUNK ARRAY
    heap_alloced[heap_alloced_size++] = chunk;


    return result;
}

void print_allocated_chunks(){
    printf("The Allocated Chunks (%zu):\n", heap_alloced_size);
    for(int i = 0; i < heap_alloced_size; i++){
        printf(" pointer: %p, size: %zu\n", heap_alloced[i].ptr, heap_alloced[i].size);
    }
}


void heap_free(void* ptr){
    for(size_t i = 0; i < heap_alloced_size; i++){
        if(heap_alloced[i].ptr == ptr){

        }
    }
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

    print_allocated_chunks();

    heap_free(root);
    
    return 0;
}