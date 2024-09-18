#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <assert.h>

#define RANGE_MIN -2137
#define RANGE_MAX 2137

// Fields:
// data - contains integer type data
// next - pointer to next node
typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

// Fields:
// head - first element of the list
// size - size of the list
typedef struct {
    Node* head;
    size_t size;
} IntList;

// Initializes IntList of size n
// All data is set to 0
IntList* init_list(size_t n) {
    assert(n > 0 && "List size must be over 0");

    IntList* list = (IntList*)malloc(sizeof(IntList));
    list->size = n;

    list->head = (Node*)calloc(1, sizeof(Node));
    Node* curr = list->head;
    for (size_t i = 1; i < n; i++) {
        Node* new = (Node*)calloc(1, sizeof(Node));
        curr->next = new;
        curr = curr->next;
    }
    return list;    
}

// Frees list and all its nodes
void free_list(IntList* list) {
    Node* curr = list->head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

// Prints list to stdout
void print_list(IntList* const list) {
    Node* curr = list->head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    putchar('\n');
}

// Fills list with random integers
void fill_list(IntList* const list) {
    Node* curr = list->head;
    
    while (curr != NULL) {
        curr->data = rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN;
        curr = curr->next;
    }
}

void swap_nodes(Node* a, Node* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// Sorts list in O(n^2)
void sort_list(IntList* const list) {
    for (int i = list->size - 2; i >= 0; i--) {
        Node* first = list->head;
        Node* second = list->head->next;
        for (int j = 0; j <= i; j++) {
            if (first->data > second->data) {
                swap_nodes(first, second);
            }
            first = second;
            second = second->next;
        }
    }
}

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

int main() {
    srand(time(NULL));
    size_t n;
    printf("How many elements in list: ");
    if (scanf("%lu", &n) == 0) {
        die("Incorrect input!\n");
    }
    if (n == 0) {
        die("List size must be over 0!\n");
    }

    IntList* list = init_list(n);
    fill_list(list);
    print_list(list);
    sort_list(list);
    printf("\nSorted list\n");
    print_list(list);

    free_list(list);
    return EXIT_SUCCESS;
}