#include "table.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int hash(char *some_value)
{
    int res = 0;
    int i = 0;

    for (i = 0; some_value[i] != '\0'; i++)
    {
        res = res + some_value[i];
    }
    return res;
}

table_t *table_create(int size){

    table_t * new_table = (table_t *)calloc(1,sizeof(table_t)) ;
    new_table->tab = calloc(size,sizeof(list_t*));

    new_table->size = size;
    for (int i = 0; i<size; i++) {

        new_table->tab[i] = list_create();
    }

    return new_table;


}

void table_destroy(table_t *one_table){

    int size = one_table->size;
    for (int i = 0; i<size; i++) {
        list_destroy(one_table->tab[i]);

    }
    free(one_table->tab);
    free(one_table);

}

int table_indexof(table_t *one_table, char *one_key){

    int size = one_table->size;
    return abs(hash(one_key) % (size-1));

}

bool table_add(table_t *one_table, char *one_key, char *one_value){

    int index = table_indexof(one_table,one_key);
    list_t * liste = one_table->tab[index];
    // if (list_contains(liste,one_key)) {
    //     return false;
    // }

    list_prepend(liste,one_key,one_value);
    return true;
    
}

bool table_contains(table_t *one_table, char *one_key){

    int index = table_indexof(one_table,one_key);
    list_t * liste = one_table->tab[index];
    if (list_contains(liste,one_key)) {
        return true;
    }

    return false;

}

char *table_get(table_t *one_table, char *one_key){

    int index = table_indexof(one_table,one_key);
    list_t * liste = one_table->tab[index];
    
    return list_find(liste,one_key);

}
