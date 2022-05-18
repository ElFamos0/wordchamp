#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "naif.h"
#include "open_dict.h"

linked_list_t* generateList() {
    linked_list_t* liste = list_create();
    char ** dico = opendict("../dico.txt", int * n);
    for (int i = 0; i < tailledico; i++) {
        list_append(liste, dico[i]);
    }
    return liste;
}

void extractList(linked_list_t* liste, array_t absentes, strInt_t[] jaunes, strInt_t[] vertes) {

}