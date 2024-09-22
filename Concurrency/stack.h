#ifndef __STACK
#define __STACK

#include <sys/types.h>

typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

typedef struct {
    Node* top;
    size_t size;
} Stack;

// Dynamically allocates stack struct and initializes its elements
Stack* init_stack();

// Frees stack and all remaining nodes
void free_stack(Stack* stack);

// Pushes element to the top of the stack
void stack_push(Stack* stack, int data);

// Returns top stack element
int stack_peek(Stack* stack);

// Removes element from the top of the stack and
// returns it
int stack_pop(Stack* stack);

#endif