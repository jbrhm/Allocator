#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define HEAP_CAPACITY 640000
#define HEAP_ALLOCED_CAPACITY 640000
#define HEAP_FREED_CAPACITY 640000
#define CHUNK_LIST_CAPACITY 1024

#define TODO() do { fprintf(stderr, "%s:%d: TODO: %s has yet to implemented\n", __FILE__, __LINE__, __FUNCTION__); abort(); }while(0)


typedef struct
{
    char* ptr;
    size_t size;
}  Heap_Chunk;

typedef struct
{
    size_t count;
    Heap_Chunk chunks[CHUNK_LIST_CAPACITY];
}Heap_Chunk_List;

void chunk_list_dump(const Heap_Chunk_List* list){
    printf("The Allocated Chunks (%zu) starting at %p:\n", list->count, list->chunks);
    for(int i = 0; i < list->count; i++){
        printf(" pointer: %p, size: %zu, address of chunk: %p\n", list->chunks[i].ptr, list->chunks[i].size, &(list->chunks[i]));
    }
}

int chunk_start_compare(const void* a, const void* b){
    const Heap_Chunk* a_chunk = a;
    const Heap_Chunk* b_chunk = b;
    return a_chunk->ptr - b_chunk->ptr;
}

int chunk_list_find(const Heap_Chunk_List* list, void* ptr){
    Heap_Chunk key;
    key.ptr = ptr;
    Heap_Chunk* result = bsearch(&key, list->chunks, list->count, sizeof(list->chunks[0]), chunk_start_compare);
    if(result != 0){
        assert(list->chunks <= result);

        return (result - list->chunks) / sizeof(list->chunks[0]);
    }else{
        return -1;
    }
}

void chunk_list_insert(Heap_Chunk_List* list, void* ptr, size_t size){
    assert(list->count < CHUNK_LIST_CAPACITY);
    list->chunks[list->count].ptr = ptr;
    list->chunks[list->count].size = size;

    for(size_t i = list->count; i > 0 && list->chunks[i].ptr < list->chunks[i - 1].ptr; --i){
        const Heap_Chunk t = list->chunks[i];
        list->chunks[i] = list->chunks[i - 1];
        list->chunks[i - 1] = t;
    }

    list->count += 1;
}

int chunk_list_remove(Heap_Chunk_List* list, size_t index){
    //ASSERT THE INDEX IS WITHIN THE LIST OF CHUNKS
    assert(index < list->count);

    //FROM THE STARTING POINT MOVE THE FOLLOWING CHUNK INTO ITS PLACE
    for(size_t i = index; i < list->count - 1; ++i){
        list->chunks[i] = list->chunks[i + 1];
    }
    list->count -= 1;
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
    if(ptr != NULL){
        //GET THE INDEX OF THE PTR IN THE ALLOCATED CHUNKS
        const int index = chunk_list_find(&alloced_chunks, ptr);

        //IF THE INDEX IS LESS THAN ZERO THEN SOMETHING WENT WRONG
        assert(index >= 0);

        //INSERT THE FREED CHUNK BACK INTO THE LIST OF FREED CHUNKS 
        chunk_list_insert(&freed_chunks, alloced_chunks.chunks[index].ptr, alloced_chunks.chunks[index].size);
        
        //REMOVE THE FREED CHUNK FROM THE ALLOCATED CHUNKS
        chunk_list_remove(&alloced_chunks, (size_t) index);
    }

}

void heap_collect(){
    TODO();
}


int main(){
    for(int i = 0; i < 100; i++){
        void* p = heap_alloc(i);
        printf("index %d \n", i);
        if(i % 2 == 0){
            heap_free(p);
        }
    }

    chunk_list_dump(&alloced_chunks);
    chunk_list_dump(&freed_chunks);

    return 0;
}