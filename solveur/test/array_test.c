#include <stdio.h>
#include "../src/array.h"

int main() {
    char elem1[30] = "Hello 1";
    char elem2[30] = "Hello 2";
    array_t *array = create_array(sizeof(char[30]));
    add_element(array, 0, &elem1);
    add_element(array, 1, &elem2);
    char * elemptr = get_array_element(array, 0);
    printf("%s\n", elemptr);
    elemptr = get_array_element(array, 1);
    printf("%s\n", elemptr);
    free_array(array);
}
