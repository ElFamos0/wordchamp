#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "dico.h"

int main() {

    table_t * table = dico_load("../../../dicoz.txt");


    for(int i= 248; i<249; i++) {
        list_print(table->tab[i]);
    }
    
    int i = 248;

    list_t * liste = table->tab[i];

    int size;
    char *** arr_list = list_to_arr(liste,&size);


    for(int i =0; i< size; i++) {

        printf("%s\n", (*arr_list)[i]);

    }

    destroy_list_arr(arr_list,size);

    table_destroy(table);

    

}
