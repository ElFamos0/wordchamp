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

char** opendict_size(char * filename, int taille, int * n){
    // function to open a file and put every word with a length of taille in an array
    // the array is returned and the number of words is returned in n
    // the array is allocated with malloc

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

    int taille_file = atoi(c);

    char **arr;
    arr = (char **)malloc(taille_file * sizeof(char *));
    int ind = 0;

    char mot[26] = "";

    while (!feof(ptr)) {
        ch = fgetc(ptr);
        if (ch != '\n') {
            strncat(mot, &ch, 1);

        }
        else {
            if (strlen(mot) == taille) {
                arr[ind] = (char*) malloc(sizeof(char)*26);
                strcpy(arr[ind], mot);
                ind += 1;
            }
            strcpy(mot,"");
        }  
    }

    *n = ind;

    fclose(ptr);
    return arr;
}

int openwsolf(){

    FILE* ptr;
    char ch;
    ptr = fopen("wsolf.txt", "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
 
    char c[50] = "";
 

    while (!feof(ptr) && ch != '\n') {
        ch = fgetc(ptr);
        strncat(c, &ch, 1);
    }

    int taille = atoi(c);

    return taille;

}
