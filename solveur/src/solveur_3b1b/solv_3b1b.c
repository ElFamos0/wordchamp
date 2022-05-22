#include "solv_3b1b.h"
#include <stdio.h>
#include <stdlib.h>


pattern_t * create_pattern(int * val, char * guess) {

    pattern_t * new_result = (pattern_t *)calloc(1,sizeof(pattern_t)) ;
    int size = strlen(guess);
    new_result->val = (int *)calloc(size,sizeof(int));

    memcpy(new_result->val, val, size * sizeof(int));

    new_result->guess = (char *)calloc(size+1,sizeof(char));

    strcpy(new_result->guess,guess);

    return new_result;

}
void destroy_pattern(pattern_t * result){

    free(result->val);
    free(result->guess);
    free(result);
}


void possible_pre(int ** count_arr, bool ** bool_arr, pattern_t * result) {

    *count_arr = (int *)calloc(26, sizeof(int));
    *bool_arr = (bool *)calloc(26, sizeof(int));

    int n = strlen(result->guess);
    for(int i = 0; i < n ; i++) {

        if (result->val[i] >= 1) {
            (*count_arr)[result->guess[i] -65] += 1;
        }

        else {
            (*bool_arr)[result->guess[i] -65] = true;
        }
    }
}

int count_occ(char * string, char c){

    int retour = 0;
    int n = strlen(string);
    for(int i = 0;i<n;i++) {

        if (string[i] == c) {
            retour +=1;
        }
    }
    return retour;
}

void print_pattern(pattern_t * pattern) {

    char * word = pattern->guess;
    int * val = pattern->val;

    int size = strlen(word);

    printf("{{%s},%d",word,val[0]);
    for(int j = 1; j< size;j++){

        printf(",%d",val[j]);
    }
    printf("}}\n");
        

}




bool possible(char * word, pattern_t * result, int * count_arr, bool * bool_arr){

    int n = strlen(result->guess);
    
    for(int i = 0; i < n ; i++) {

        if (result->val[i] == 2 && result->guess[i] != word[i])  {
            return false;
        }
        else if (result->val[i] != 2 && result->guess[i] == word[i]) {return false ;}
    }

    for(int i = 0; i < 26 ; i++) {

        int count = count_occ(word,'A' +i);
        if ((bool_arr[i] && count != count_arr[i]) || (count < count_arr[i])) {return false;}
    }
    return true;
}


void gen_val_array(int *** val_arr, int size){

    *val_arr = (int **)malloc((int)pow(3,size)*sizeof(int *));

    for(int i = 0; i<(int)pow(3,size); i++ ) {

        (*val_arr)[i] = (int *)malloc(size*sizeof(int));

        memset((*val_arr)[i], 0, size*sizeof(int) );
        int temp = i;
        int c = 0;
        for(int j = 0; j< size; j++) {
            c = temp/(int)pow(3,size-1-j);
            temp = temp - c*(int)pow(3,size-1-j);
            (*val_arr)[i][j] = c;
        }
    }

}
void destroy_val_array(int *** val_arr, int size) {

    for(int i = 0; i<(int)pow(3,size); i++ ) {

        free((*val_arr)[i]);
    }
    free(*val_arr);
}


pattern_t *** generate_all_pattern(char * word,int ** val_arr) {

    int size = strlen(word);
    pattern_t *** new_pattern_arr = (pattern_t ***)calloc(1,sizeof(pattern_t **)) ;
    (*new_pattern_arr) = (pattern_t **)malloc((int)pow(3,size)*sizeof(pattern_t *)) ;
    for(int i = 0; i<(int)pow(3,size); i++ ) {

        (*new_pattern_arr)[i] = create_pattern(val_arr[i],word);
    }
    return new_pattern_arr;
}

void destroy_pattern_arr(pattern_t *** pattern_arr ){


    int size = strlen((*pattern_arr)[0]->guess);
    int taille = (int)pow(3,size);

    for(int i = 0; i < taille; i++) {

        destroy_pattern( (*pattern_arr)[i]);
    }

    free(*pattern_arr);
    free(pattern_arr);
}

