#ifndef HEAP_H_
#define HEAP_H_

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define TODO() do { fprintf(stderr, "%s:%d: TODO: %s has yet to implemented\n", __FILE__, __LINE__, __FUNCTION__); abort(); }while(0)

#define HEAP_CAPACITY_BYTES 640000
static_assert(HEAP_CAPACITY_BYTES % sizeof(void*) == 0, "THE HEAP CAPACITY IS NOT DIVISIBLE BY THE SIZE OF THE POINTER");
#define HEAP_CAPACITY (HEAP_CAPACITY_BYTES/sizeof(void*))


#define CHUNK_LIST_CAPACITY 1024

static_assert(HEAP_CAPACITY % sizeof(uintptr_t) == 0, "THE HEAP CAPACITY IS NOT DIVISIBLE BY THE SIZE OF THE POINTER");
extern uintptr_t heap[HEAP_CAPACITY];

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

extern Heap_Chunk_List alloced_chunks;
extern Heap_Chunk_List freed_chunks;
extern Heap_Chunk_List temp_chunks;

void chunk_list_insert(Heap_Chunk_List* list, void* ptr, size_t size);

void chunk_list_merge(Heap_Chunk_List* dst, Heap_Chunk_List* src);

void* heap_alloc(size_t size_bytes);

void chunk_list_dump(const Heap_Chunk_List* list);

int chunk_list_find(const Heap_Chunk_List* list, uintptr_t* ptr);

int chunk_list_remove(Heap_Chunk_List* list, size_t index);

void heap_free(void* ptr);

void heap_collect();

#endif //HEAP_H_