#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {

    table_t * table = table_create(1);
    table_add(table,"cle1","maison1");
    table_add(table,"cle2","maison2");
    table_add(table,"cle3","maison3");
    table_add(table,"cle4","maison4");

    list_print(table->tab[0]);

    int a1 = table_contains(table,"cle5");
    int a2 = table_contains(table,"cle4");
    
    printf("%d,%d\n",a1,a2);

    printf("%s\n",table_get(table,"cle3"));

    int ind = table_indexof(table,"cle1");

    list_print(table->tab[ind]);

    printf("\n");

    table_destroy(table);
}