#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    list_t * new_liste = list_create();
    printf("%d",list_is_empty(new_liste));
    list_print(new_liste);
    
    list_append(new_liste,"cle1","maison1");
    list_append(new_liste,"cle2","maison2");
    list_append(new_liste,"cle3","maison3");
    list_print(new_liste);

    printf("%d",list_contains(new_liste,"cle2"));
    printf("%d",list_contains(new_liste,"cle4"));

    printf("%s",list_find(new_liste,"cle2"));

    list_destroy(new_liste);

}
