#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/open_dict.h"

int main() {

    char ** arr;
    char filename[] = "dico.txt";

    int n;
    arr = (char**) opendict(filename, &n);

    for (int i = 0; i<n;i++) {

        printf("%s\n", arr[i]);
        free(arr[i]);

    }

    free(arr);

    int taille = openwsolf();

    printf("Taille : %d \n", taille);

}
