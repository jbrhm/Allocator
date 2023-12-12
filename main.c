#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define HEAP_CAPACITY 640000
#define HEAP_ALLOCED_CAPACITY 640000
#define HEAP_FREED_CAPACITY 640000

#define TODO() do { fprintf(stderr, "%s:%d: TODO: %s has yet to implemented\n", __FILE__, __LINE__, __FUNCTION__); abort(); }while(0)


typedef struct
{
    void* ptr;
    size_t size;
}  Heap_Chunk;

typedef struct
{
    size_t count;
    Heap_Chunk chunks[HEAP_ALLOCED_CAPACITY];
}Heap_Chunk_List;

void chunk_list_dump(const Heap_Chunk_List* list){
    printf("The Allocated Chunks (%zu):\n", list->count);
    for(int i = 0; i < list->count; i++){
        printf(" pointer: %p, size: %zu\n", list->chunks[i].ptr, list->chunks[i].size);
    }
}

int chunk_list_find(const Heap_Chunk_List* list, void* ptr){
    TODO();
}

void chunk_list_insert(void* ptr, size_t size){
    TODO();
}

int chunk_list_remove(Heap_Chunk_List* list, size_t index){
    TODO();
}

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

Heap_Chunk heap_alloced[HEAP_ALLOCED_CAPACITY] = {0};
size_t heap_alloced_size = 0;

Heap_Chunk heap_freed[HEAP_FREED_CAPACITY] = {0};
size_t heap_freed_size = 0;

Heap_Chunk_List alloced_chunks = {0};
Heap_Chunk_List freed_chunks = {0};

void* heap_alloc(size_t size){

    //IF THE SIZE OF THE ALLOCATED CHUNK IS 0 RETURN NULL SO ALL OF THE POINTERS RETURNED ARE EITHER UNIQUE OR NULL
    if(size == 0){
        return NULL;
    }

    //ASSERT THE ALLOCATED MEMORY IS WITHIN THE HEAP CAPACITY
    assert(heap_size + size <= HEAP_CAPACITY);

    //GET THE HEAP PTR POINTING TO THE NEW ALLOCATED DATA
    void* ptr = heap + heap_size;

    //UPDATE THE HEAP SIZE
    heap_size += size;

    //CREATE THE CHUNK TO BE ALLOCATED
    chunk_list_insert(&alloced_chunks, ptr, size);

    //RETURN THE POINTER TO THE MEMORY THAT WAS ALLOCATED
    return ptr;
}




void heap_free(void* ptr){
    TODO();
}

void heap_collect(){
    TODO();
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