#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/open_dict.h"

int main() {

    char ** arr;
    char filename[] = "../dicoz.txt";

    int n;
    arr = (char**) opendict(filename, &n);

    for (int i = 0; i<n;i++) {

        printf("%s\n", arr[i]);
        free(arr[i]);

    }

    free(arr);

    char ** arr2;
    arr2 = (char**) opendict_size(filename, 5, &n);

    for (int i = 0; i<n;i++) {
        printf("%s\n", arr2[i]);
        free(arr2[i]);

    }

    free(arr2);


    //int taille = openwsolf();

    //printf("Taille : %d \n", taille);

}
