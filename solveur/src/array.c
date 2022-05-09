#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

array_t * create_array(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }
    
    struct array_t *array = calloc(1, sizeof(array_t));

    if (!array) {
        return NULL;
    }

    array->data = calloc(DEFAULT_SIZE, element_size);

    if (!array->data) {
        free(array);
        return NULL;
    }

    array->capacity = DEFAULT_SIZE;
    array->element_size = element_size;

    return array;
}

void free_array(array_t *array) {
    if (!array) {
        return;
    }
    free(array->data);
    free(array);
}

int array_resize(array_t *array) {
    if (!array) {
        return 0;
    }
    if (array->size < array->capacity) {
        return 1;
    }

    size_t new_capacity = array->capacity << 1;
    char *new_data = realloc(array->data, new_capacity * array->element_size);

    if (!new_data) {
        return 0;
    }

    array->data = new_data;
    array->capacity = new_capacity;
    return 1;
}

int prepend_element(array_t *array, void *element) {
    if (!array) {
        return 0;
    }
    if (!element) {
        return 0;
    }

    return add_element(array, 0, element);
}

int append_element(array_t *array, void *element) {
    if (!array) {
        return 0;
    }
    if (!element) {
        return 0;
    }

    return add_element(array, array->size, element);
}

int add_element(array_t *array, size_t index, void * element) {
    if (!array) {
        return 0;
    }
    if (index > array->size) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }

    if (!array_resize(array)) {
        return 0;
    }

    // On calcule les offsets pour l'element a ajouter (là où il doit être et là ou le prochain sera bouger)
    char * const elementDest = array->data + index * array->element_size;
    char * const moveDest = elementDest + array->element_size;

    memmove(moveDest, elementDest, array->element_size * (array->size - index));
    memcpy(elementDest, element, array->element_size);

    array->size++;
    return 1;
}


int remove_element(array_t *array, size_t index) {
    if (!array) {
        return 0;
    }
    if (index > array->size) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }

    // On calcule les offsets pour l'element a ajouter (là où il doit être et là ou le prochain sera bouger)
    char * const currentPos = array->data + index * array->element_size;
    char * const nextPos = currentPos + array->element_size;

    memmove(currentPos, nextPos, array->element_size * (array->size - (index + 1)));

    array->size--;
    return 1;
}

void * get_array_element(array_t *array, size_t index) {
    if (!array) {
        return NULL;
    }
    if (index >= array->size) {
        return NULL;
    }

    return array->data + (index * array->element_size);
}

int get_array_size(array_t *array) {
    if (!array) {
        return 0;
    }
    return array->size;
}

void for_each_element(array_t *array, void (*callback)(void *element)) {
    if (!array) {
        return;
    }
    if (!callback) {
        return;
    }
    for (size_t i = 0; i < array->size; i++) {
        callback(array->data + (i * array->element_size));
    }
}