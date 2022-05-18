#include <stdio.h>
#include "../src/array.h"

void print_array(array_t * array) {
    printf("[");
    for (size_t i = 0; i < array->size; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", get_array_element(array, i));
    }
    printf("]\n");
}

int main() {
    int elem1 = 1;
    int elem2 = 2;
    int elem3 = 3;
    int elem4 = 4;

    array_t *array = create_array(sizeof(int));

    append_element(array, &elem1);
    append_element(array, &elem2);
    prepend_element(array, &elem4);
    add_element(array, 1, &elem3);

    print_array(array);
    remove_element(array, 0);
    print_array(array);
    remove_element(array, 1);
    print_array(array);

    free_array(array);
}
