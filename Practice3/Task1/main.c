#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *array;
    int size;
    int capacity;
} ArrayList;

void initArrayList(ArrayList *list) {
    list->array = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
}

void ensureCapacity(ArrayList *list) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (int *)realloc(list->array, list->capacity * sizeof(int));
    }
}

void add(ArrayList *list, int item) {
    ensureCapacity(list);
    list->array[list->size++] = item;
}

void insert(ArrayList *list, int index, int item) {
    ensureCapacity(list);
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    for (int i = list->size; i > index; i--) {
        list->array[i] = list->array[i - 1];
    }

    list->array[index] = item;
    list->size++;
}

int size(const ArrayList *list) {
    return list->size;
}

void removeItem(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }

    list->size--;
}

void set(ArrayList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    list->array[index] = item;
}

int get(const ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    return list->array[index];
}

void freeArrayList(ArrayList *list) {
    free(list->array);
}

int main() {
    ArrayList list;
    initArrayList(&list);

    add(&list, 1);
    add(&list, 2);
    add(&list, 3);

    insert(&list, 1, 4);

    for (int i = 0; i < size(&list); i++) {
        printf("%d ", get(&list, i));
    }

    freeArrayList(&list);

    return 0;
}

