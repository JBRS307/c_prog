#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct Node Node;
struct Node {
    void* data;
    Node* next;
    Node* prev;
};

typedef struct {
    Node* head;
    Node* tail;
    size_t data_size;
    size_t length;
} LinkedList;

// Initializes double empty double linked list
// with size of element at elem_size
LinkedList* linked_list_init(size_t elem_size) {
    LinkedList* list = (LinkedList*)calloc(1, sizeof(LinkedList));
    list->data_size = elem_size;
    return list;
};

static Node* node_initialize(void* data, size_t data_size) {
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(data_size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    
    if (memcpy(node->data, data, data_size) == NULL) {
        free(node->data);
        free(node);
        return NULL;
    }
    return node;
}

// Adds element to the end of the list
// At most data_size elements are copied
int linked_list_push_back(LinkedList* list, void* data) {
    Node* new = node_initialize(data, list->data_size);
    if (new == NULL) {
        return -1;
    }

    if (list->tail) {
        new->prev = list->tail;
        list->tail->next = new;
        list->tail = new;
    } else {
        // Occurs only when there are no elements in list
        list->head = list->tail = new;
    }
    list->length++;
    return 0;
}

// Adds element to the begining of the list
// copies at most data_size bytes
int linked_list_push_front(LinkedList* list, void* data) {
    Node* new = node_initialize(data, list->data_size);
    if (new == NULL) {
        return -1;
    }

    if (list->head) {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    } else {
        list->head = list->tail = new;
    }
    list->length++;
    return 0;
}

// Returns pointer to data stored in node at index idx
// IT DOES NOT COPY DATA
void* linked_list_at(const LinkedList* list, size_t idx) {
    if (idx >= list->length) {
        return NULL;
    }

    const Node* res = list->head;
    for (size_t i = 0; i < idx; i++) {
        res = res->next;
    }

    return res->data;
}


void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void perror_die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {


    return EXIT_SUCCESS;
}