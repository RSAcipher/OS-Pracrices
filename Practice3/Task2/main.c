#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

void initLinkedList(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

void add(LinkedList *list, int item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

void insert(LinkedList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

int size(const LinkedList *list) {
    return list->size;
}

void removeItem(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    Node *temp;
    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        temp = current->next;
        current->next = current->next->next;
    }

    free(temp);
    list->size--;
}

void set(LinkedList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->data = item;
}

int get(const LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

void freeLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    LinkedList list;
    initLinkedList(&list);

    add(&list, 1);
    add(&list, 2);
    add(&list, 3);

    insert(&list, 1, 4);

    for (int i = 0; i < size(&list); i++) {
        printf("%d ", get(&list, i));
    }

    freeLinkedList(&list);

    return 0;
}
