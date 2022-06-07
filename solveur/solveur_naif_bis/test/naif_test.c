#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "../src/naif.h"
#include "../src/linked_list.h"
#include "../src/strInt.h"


int main() {
    linked_list_t* liste_test = generateList();

    char** absentes = malloc(sizeof(char *)*1);
    strInt_t* jaunes = malloc(sizeof(strInt_t)*1);
    strInt_t* vertes = malloc(sizeof(strInt_t)*1);

    absentes[0]="Z";
    
    jaunes[0].lettre="I";
    jaunes[0].position=2;

    vertes[0].lettre="R";
    vertes[0].position=4;

    extractList(liste_test, 1, absentes, 1, jaunes, 1, vertes);
    free(jaunes);
    free(vertes);
    free(absentes);
    printf("%s", list_first(liste_test));
    list_destroy(liste_test);
    return 69;
}