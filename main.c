#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define HEAP_CAPACITY 640000
#define HEAP_ALLOCED_CAPACITY 640000
#define HEAP_FREED_CAPACITY 640000
#define CHUNK_LIST_CAPACITY 1024

#define TODO() do { fprintf(stderr, "%s:%d: TODO: %s has yet to implemented\n", __FILE__, __LINE__, __FUNCTION__); abort(); }while(0)


typedef struct
{
    uintptr_t* ptr;
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
        printf(" pointer: %p, size: %zu, address of chunk: %p\n", (void*) list->chunks[i].ptr, list->chunks[i].size, &(list->chunks[i]));
    }
}

int chunk_list_find(const Heap_Chunk_List* list, uintptr_t* ptr){
    //LINEARLY SEARCH FOR THE NEXT FREE CHUNK
    for(int i = 0; i < list->count; i++){
        if(list->chunks[i].ptr == ptr){
            return i;
        }
    }

    return -1;
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

void chunk_list_merge(Heap_Chunk_List* dst, Heap_Chunk_List* src){
    dst->count = 0;

    for(size_t i = 0; i < src->count; ++i){
        const Heap_Chunk chunk = src->chunks[i];

        if(dst->count > 0){
            Heap_Chunk* top_chunk = &dst->chunks[dst->count -1];

            if(top_chunk->ptr + top_chunk->size == chunk.ptr){
                top_chunk->size += chunk.size;
            }else{
                chunk_list_insert(dst, chunk.ptr, chunk.size);
            }
        }else{
            chunk_list_insert(dst, chunk.ptr, chunk.size);
        }
    }
}

static_assert(HEAP_CAPACITY % sizeof(uintptr_t) == 0, "THE HEAP CAPACITY IS NOT DIVISIBLE BY THE SIZE OF THE POINTER");
uintptr_t heap[HEAP_CAPACITY] = {0};

Heap_Chunk heap_alloced[HEAP_ALLOCED_CAPACITY] = {0};
size_t heap_alloced_size = 0;

Heap_Chunk heap_freed[HEAP_FREED_CAPACITY] = {0};
size_t heap_freed_size = 0;

Heap_Chunk_List alloced_chunks = {0};
Heap_Chunk_List freed_chunks =  {
                                .count = 1,
                                .chunks = {{.ptr = heap, .size = sizeof(heap)}}
                                };
Heap_Chunk_List temp_chunks = {0};

void* heap_alloc(size_t size_bytes){

    //ADUST THE ALLOCATED MEMORY SO THAT IT ALIGNS WITH THE SIZE EXPECTED, IN THIS CASE sizeof(uintptr_t)
    const size_t size_words = (size_bytes + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);

    //MAKE SURE THERE IS ACTUALLY SOMETHING TO ALLOCATE SO ALL OF THE POINTERS RETURNED WILL BE UNIQUE
    if(size_words <= 0){
        return NULL;
    }

    //MERGE THE ADJACENT FREE CHUNKS BACK TOGETHER
    chunk_list_merge(&temp_chunks, &freed_chunks);

    //REASSIGN THE FREED CHUNKS TO THE TEMPORARY MERGED CHUNKS
    freed_chunks = temp_chunks;

    //ITERATE OVER THE SIZE OF THE FREE CHUNKS TO FIND ONE THAT FITS THE SIZE NECESSARY
    for(size_t i = 0; i < freed_chunks.count; i++){
        //GET THE CHUNK
        const Heap_Chunk chunk = freed_chunks.chunks[i];
        if(chunk.size >= size_words){
            //REMOVE THE CHUNK FROM THE FREE LIST
            chunk_list_remove(&freed_chunks, i);

            //GET THE POINTER TO THE CHUNK
            const void* ptr = chunk.ptr;

            //FIND THE TAIL SIZE OF THE NEWLY ALLOCATED CHUNK
            const size_t tail_size = chunk.size - size_words; 

            //FIND THE POINTER TO THE TAIL MEMORY OF THE NEWLY ALLOCATED CHUNK
            const void* tail_ptr = chunk.ptr + size_words;
            //INSERT THE NEWLY ALLOCATED CHUNK INTO THE ALLOCATED CHUNKS
            chunk_list_insert(&alloced_chunks, chunk.ptr, size_words);

            //IF THE TAIL SIZE IS GREATER THAN ZERO THEN APPEND THE TAIL CHUNK BACK INTO THE FREE LIST
            if(tail_size > 0){
                chunk_list_insert(&freed_chunks, tail_ptr, tail_size);
                
            }
            return ptr;
        }
    }

    //IF THE HEAP IS OUT OF MEMORY
    return NULL;
}




void heap_free(void* ptr){
    if(ptr != NULL){
        //GET THE INDEX OF THE PTR IN THE ALLOCATED CHUNKS
        const int index = chunk_list_find(&alloced_chunks, ptr);

        //IF THE INDEX IS LESS THAN ZERO THEN SOMETHING WENT WRONG
        assert(index >= 0);

        assert(ptr == alloced_chunks.chunks[index].ptr);

        //INSERT THE FREED CHUNK BACK INTO THE LIST OF FREED CHUNKS 
        chunk_list_insert(&freed_chunks, alloced_chunks.chunks[index].ptr, alloced_chunks.chunks[index].size);
        
        //REMOVE THE FREED CHUNK FROM THE ALLOCATED CHUNKS
        chunk_list_remove(&alloced_chunks, (size_t) index);
    }

}

void heap_collect(){
    TODO();
}

#define N 10

void* ptrs[N] = {0};

int main(){
    for(int i = 0; i < N; ++i){
        ptrs[i] = heap_alloc(i);
    }

    // for(int i = 0; i < N; ++i){
    //     if(i % 2 == 0){
    //         heap_free(ptrs[i]);
    //     }
    // }

    heap_alloc(10);

    chunk_list_dump(&alloced_chunks);
    chunk_list_dump(&freed_chunks);

    return 0;
}