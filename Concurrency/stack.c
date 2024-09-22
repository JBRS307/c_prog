#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// Dynamically allocates stack struct and initializes its elements
Stack* init_stack() {
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Unable to allocate Stack!\n");
        return NULL;
    }
    return stack;
}

// Frees stack and all remaining nodes
void free_stack(Stack* stack) {
    Node* curr = stack->top;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(stack);
}

// Pushes element to the top of the stack
void stack_push(Stack* stack, int data) {
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL) {
        fprintf(stderr, "Unable to allocate Node, element not pushed to stack!\n");
        return;
    }
    new->data = data;
    new->next = stack->top;
    stack->top = new;
    stack->size++;
}

// Returns top stack element
int stack_peek(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty!\n");
        return 0;
    }
    return stack->top->data;
}

// Removes element from the top of the stack and
// returns it
int stack_pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is emopty!\n");
        return 0;
    }

    Node* rem = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    int data = rem->data;
    free(rem);
    return data;
}