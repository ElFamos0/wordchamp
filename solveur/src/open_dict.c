#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "open_dict.h"
 

char ** opendict(char * filename, int * n)
{
    FILE* ptr;
    char ch;
    ptr = fopen(filename, "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    char c[50] = "";
 

    while (!feof(ptr) && ch != '\n') {
        ch = fgetc(ptr);
        strncat(c, &ch, 1);
    }

    int taille = atoi(c);

    char **arr;
    arr = (char **)malloc(taille * sizeof(char *));
    int ind = 0;
    char mot[26] = "";
    

    while (!feof(ptr)) {
        ch = fgetc(ptr);
        if (ch != '\n') {
            strncat(mot, &ch, 1);

        }
        else {
            arr[ind] = (char*) malloc(sizeof(char)*26);
            strcpy(arr[ind], mot);
            strcpy(mot,"");
            ind += 1;
        }  
    }

    *n = taille;

    fclose(ptr);
    return arr;
}
