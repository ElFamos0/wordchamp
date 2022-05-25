#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

list_t *list_create() {
    list_t *list = calloc(1, sizeof(list_t));

    assert(list != NULL);

    list->data = calloc(DEFAULT_CAPACITY, sizeof(element_t *));

    if (!list->data) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = DEFAULT_CAPACITY;
}

void list_destroy(list_t *list) {
    assert(list!= NULL);
    for (int i = 0; i < list->size; i++) {
        free(list->data[i]->key);
        free(list->data[i]);
    }    
    free(list->data);
    free(list);
}

bool list_is_empty(list_t *list) {
    assert(list != NULL);
    return list->size == 0;
}

int list_resize(list_t *list) {
    assert(list != NULL);
    if(list->size < list->capacity) {
        return 1;
    }

    int new_capacity = list->capacity * 2;
    element_t ** new_data = realloc(list->data, new_capacity * sizeof(element_t *));

    if (!new_data) {
        return 0;
    }

    list->capacity = new_capacity;
    list->data = new_data;
    return 1;
}

void list_add(list_t *list, size_t index, char *key, void * value) {
    assert(list != NULL);
    assert(key != NULL);
    assert(index <= list->size);
    assert(index >= 0);

    if (!list_resize(list)) {
        return;
    }


    element_t * elem = malloc(sizeof(element_t));
    elem->key = strdup(key);
    elem->value = value;

    element_t ** dest = &(list->data[index]);
    element_t ** src = dest + sizeof(element_t *);
    int const size = (list->size - index) * sizeof(element_t *);

    memmove(dest, src, size);

    *dest = elem;

    list->size++;
}

void list_append(list_t *list, char *key, void * value) {
    assert(list != NULL);
    assert(key != NULL);

    if (!list_resize(list)) {
        return;
    }

    list_add(list, list->size, key, value);
}

void * list_get(list_t *list, size_t index) {
    assert(list != NULL);
    assert(index <= list->size);
    assert(index >= 0);

    return list->data[index];
}

void element_print(element_t * element) {
    assert(element != NULL);

    printf("    %s:%p,\n", element->key, element->value);
}

void list_print(list_t *list) {
    assert(list != NULL);

    printf("{\n");
    for (int i = 0; i < list->size; i++) {
        element_print(list_get(list, i));
    }
    printf("}\n");
}

bool list_contains(list_t *list, char *key) {
    assert(list != NULL);
    assert(key != NULL);

    for (int i = 0; i < list->size; i++) {
        element_t * elemptr = (element_t *) list_get(list, i);
        if (strcmp(elemptr->key, key) == 0) {
            return true;
        }
    }
    return false;
}

void * list_find(list_t *list, char *key) {
    assert(list != NULL);
    assert(key != NULL);

    for (int i = 0; i < list->size; i++) {
        element_t * elemptr = (element_t *) list_get(list, i);
        if (strcmp(elemptr->key, key) == 0) {
            return elemptr->value;
        }
    }
    return NULL;  
}

void list_iterate(list_t *list, void (*function)(char *, void *)) {
    assert(list != NULL);
    assert(function != NULL);

    for (int i = 0; i < list->size; i++) {
        element_t * elemptr = (element_t *) list_get(list, i);
        function(elemptr->key, elemptr->value);
    }
}