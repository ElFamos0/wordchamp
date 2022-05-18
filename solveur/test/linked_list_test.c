#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "../src/linked_list.h"

int main() {
    linked_list_t* myList = list_create();
    printf("List vide ? : %d\n", list_is_empty(myList) ? 1 : 0);
    list_print(myList);
    list_append(myList, "un");
    printf("List vide ? : %d\n", list_is_empty(myList) ? 1 : 0);
    list_print(myList);
    list_prepend(myList, "zero");
    list_print(myList);
    list_insert(myList, "deux", 1);
    list_print(myList);
    printf("Premier : %s\n", list_first(myList));
    printf("Dernier : %s\n", list_last(myList));
    printf("Element 1 : %s\n", list_get(myList, 1));
    printf("Indice de deux : %d\n", list_index_of(myList, "deux"));

    list_destroy(myList);
    return 69;
}