#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "./heap.h"

typedef struct Node Node;

struct Node {
    char x;
    Node* left;
    Node* right;
};

Node* generate_tree(size_t current_level, size_t max_level){
    if(current_level < max_level){
        Node* root = heap_alloc(sizeof(*root));
        assert((char)current_level - 'a' <= 'z');
        root->x = current_level + 'a';
        root->left = generate_tree(current_level + 1, max_level);
        root->right = generate_tree(current_level + 1, max_level);
        return root;
    }else{
        return NULL;
    }
}

void print_tree(Node* root, size_t level_current){
    printf("char = %c level = %zu\n", root->x, level_current);
    if(root->right != NULL){
        print_tree(root->right, level_current + 1);
    }
    if(root->left != NULL){
        print_tree(root->left, level_current + 1);
    }
}

#define N 10

void* ptrs[N] = {0};

int main(){
    
    Node* root = generate_tree(0, 3);

    print_tree(root, 0);

    printf("--------------------\n");

    size_t heap_ptrs_count = 0;
    for(size_t i = 0; i < alloced_chunks.count; ++i){

        for(size_t j = 0; j < alloced_chunks.chunks[i].size; ++j){
            uintptr_t* p = (uintptr_t*) alloced_chunks.chunks[i].ptr[j];
            if(heap <= p && p < heap + HEAP_CAPACITY){
                printf("Detected heap pointer %p\n", (void*) p);
                heap_ptrs_count++;
            }
        }
    }

    printf("Detected Pointers: %zu\n", heap_ptrs_count);

    return 0;
}