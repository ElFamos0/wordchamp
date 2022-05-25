#include "table.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "dico.h"
#include <string.h>

table_t* dico_load(char* filename){

    table_t * table = table_create(100000);

    FILE* ptr;
    char ch;
    ptr = fopen(filename, "r");
 
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    char a[50] = "";

    while (!feof(ptr) && ch != '\n') {
        ch = fgetc(ptr);
        strncat(a, &ch, 1);
    }

    int taille_file = atoi(a);

    int c = 0;

    char ligne[30];
    while (fgets(ligne, 50, ptr) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = 0;
        table_add(table,ligne,"default");
        c+=1;
    }

    // while (!feof(ptr)) {
    //     ch = fgetc(ptr);
    //     if (ch != ' ' && ch != '\'' && ch != '.' && ch != '\n' && ch != ',' && ch != ':' && ch != ';' && ch !='?' && ch != '!' && ch != ')' && ch != '(' && ch != '/'&& ch != '\r') {
    //         strncat(mot, &ch, 1);

    //     }
    //     else if (ch != '\r') {
    //         table_add(table,mot,"default");
    //         c++;
    //         // printf("%d\n",c);
            
    //         mot[0] = '\0';
            

    //         //strcpy(mot,"");
    //     }  
    // }

    
    fclose(ptr);
    return table;


}

table_t* dico_load_size(char * filename, int taille){
    // function to open a file and put every word with a length of taille in an array
    // the array is returned and the number of words is returned in n
    // the array is allocated with malloc

    FILE* ptr;
    char ch;
    ptr = fopen(filename, "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    table_t * table = table_create(100000);

    char a[50] = "";

    while (!feof(ptr) && ch != '\n') {
        ch = fgetc(ptr);
        strncat(a, &ch, 1);
    }

    int taille_file = atoi(a);

    int c = 0;

    char ligne[30];

    while (fgets(ligne, 50, ptr) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = 0;
        if (strlen(ligne) == taille) {
            table_add(table,ligne,"default");
            c+=1;
        }
        
    }

    // while (!feof(ptr)) {
    //     ch = fgetc(ptr);
    //     if (ch != '\n') {
    //         strncat(mot, &ch, 1);

    //     }
    //     else {
    //         if (strlen(mot) == taille) {
    //             arr[ind] = (char*) malloc(sizeof(char)*26);
    //             strcpy(arr[ind], mot);
    //             ind += 1;
    //         }
    //         strcpy(mot,"");
    //     }  
    // }


    fclose(ptr);
    return table;
}

