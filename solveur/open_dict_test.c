#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "open_dict.h"

int main() {

    char ** arr;
    char filename[] = "dico.txt";

    arr = (char**) opendict(filename);

    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i<n;i++) {

        printf("%s ", arr[i]);
        free(arr[i]);

    }

    free(arr);

}
