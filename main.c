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
    //MUST STAY AT THE START OF THE CODE TO GRAB THE STACK POINTER
    void* p = NULL;
    stack_base = (uintptr_t*) &p;

    for(size_t i = 0; i < 10; ++i){
        heap_alloc(i);
    }
    
    Node* root = generate_tree(0, 3);

    printf("root = %p\n", (void*) root);

    print_tree(root, 0);

    chunk_list_dump(&alloced_chunks);
    printf("\n--------------------\n");

    heap_collection();

    chunk_list_dump(&alloced_chunks);
    printf("\n--------------------\n");
    
    root = NULL;

    heap_collection();

    chunk_list_dump(&alloced_chunks);
    sprintf("\n--------------------\n");


    return 0;
}