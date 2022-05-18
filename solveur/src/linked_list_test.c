#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "linked_list.h"

int main() {
    linked_list_int_t* myList = list_create();
    printf("List vide ? : %d\n", list_is_empty(myList) ? 1 : 0);
    list_print(myList);
    list_append(myList, 1);
    printf("List vide ? : %d\n", list_is_empty(myList) ? 1 : 0);
    list_print(myList);
    list_prepend(myList, 0);
    list_print(myList);
    list_insert(myList, 2, 1);
    list_print(myList);
    printf("Premier : %d\n", list_first(myList));
    printf("Dernier : %d\n", list_last(myList));
    printf("Element 1 : %d\n", list_get(myList, 1));
    printf("Indice de 2 : %d\n", list_index_of(myList, 2));

    list_destroy(myList);
    return 69;
}