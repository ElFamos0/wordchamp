#include <stdio.h>
#include "../src/array.h"

void print_array(array_t * array) {
    printf("[");
    for (size_t i = 0; i < array->size; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%s", get_array_element(array, i));
    }
    printf("]\n");
}

int main() {
    char elem1[30] = "Hello 1";
    char elem2[30] = "Hello 2";
    char elem3[30] = "Hello 3";
    char elem4[30] = "Hello 4";

    array_t *array = create_array(sizeof(char[30]));

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
