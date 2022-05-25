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

    printf("{{%s},{%d",word,val[0]);
    for(int j = 1; j< size;j++){

        printf(",%d",val[j]);
    }
    printf("}\n");
        

}




bool possible(char * word, pattern_t * result, int * count_arr, bool * bool_arr){

    int n = strlen(result->guess);
    
    for(int i = 0; i < n ; i++) {

        if (result->val[i] == 2 && result->guess[i] != word[i])  {
            return false;
        }
        else if (result->val[i] != 2 && result->guess[i] == word[i]) {
            return false ;
            }
    }

    for(int i = 0; i < 26 ; i++) {

        int count = count_occ(word,'A' +i);
        if ((bool_arr[i] && count != count_arr[i]) || (count < count_arr[i])) {
            return false;
            }
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



bool pattern_is_possible(pattern_t * pattern) {

    char * mot = pattern->guess;
    int * val = pattern->val;
    int size = strlen(mot) ;
    char c;
    for(int i =0; i< size; i++) {

        if (val[i] == 1) { 
            c = mot[i];
            int j = 0;
            while(j<i) {
                if (val[j] == 0 && mot[j] == c) {return false;}
                j++;
            }

        }

    }
    return true;
}






pattern_t *** generate_all_pattern(char * word,int ** val_arr) {

    int size = strlen(word);
    pattern_t *** new_pattern_arr = (pattern_t ***)calloc(1,sizeof(pattern_t **)) ;
    (*new_pattern_arr) = (pattern_t **)malloc((int)pow(3,size)*sizeof(pattern_t *)) ;
    for(int i = 0; i<(int)pow(3,size); i++ ) {

        pattern_t * new_pattern = create_pattern(val_arr[i],word);
        if(pattern_is_possible(new_pattern)) {
            (*new_pattern_arr)[i] = new_pattern;
        }
        else {

            destroy_pattern(new_pattern);
            (*new_pattern_arr)[i] = NULL;
        }
    }
    return new_pattern_arr;
}

void destroy_pattern_arr(pattern_t *** pattern_arr ){


    int size = strlen((*pattern_arr)[0]->guess);
    int taille = (int)pow(3,size);

    for(int i = 0; i < taille; i++) {

        if ((*pattern_arr)[i] != NULL) {
            destroy_pattern( (*pattern_arr)[i]);
        }   
    }

    free(*pattern_arr);
    free(pattern_arr);
}

char *** all_words(table_t * table, int * size_ptr) {

    int size = 0;
    char * mot;
    char *** arr = (char ***)calloc(1,sizeof(char **)) ;
    (*arr) = (char **) malloc(sizeof(char*));

    for(int indice = 0; indice < table->size; indice ++) {

        list_t * liste = table->tab[indice];
        int taille;
        char *** arr_list = list_to_arr(liste,&taille);


        for(int i =0; i< taille; i++) {

            mot = strdup((*arr_list)[i]);
            size+=1;
            (*arr) = (char **) realloc((*arr),(size+1)*sizeof(char[30]));
            (*arr)[size-1] = mot;
        }

        destroy_list_arr(arr_list,taille);

     }
    (* size_ptr) = size;
    return arr;
}


void destroy_all_words(char *** arr, int size) {

    for(int i = 0 ; i< size; i++) {

        free((*arr)[i]);

    }

    free(*arr);
    free(arr);

}



double calculate_proba(pattern_t * pattern, table_t  * table,char *** all_words_arr,int arr_size){

    int * count;
    bool * arr;
    possible_pre(&count,&arr,pattern);
    double s = 0;
    double compteur = 0;
    for(int indice = 0; indice < arr_size; indice ++) {

        compteur +=1;
        if (possible((*all_words_arr)[indice],pattern,count,arr)) {
               s+=1;   
            }
    }

    free(count);
    free(arr);
    return s/compteur;


}


void update_possible_words(table_t * table, pattern_t * pattern){

    table_t * new_table = table_create(100000);

    int * count;
    bool * arr;
    possible_pre(&count,&arr,pattern);
    
    for(int indice = 0; indice < table->size; indice ++) {

        list_t * liste = table->tab[indice];
        int size;
        char *** arr_list = list_to_arr(liste,&size);


        for(int i =0; i< size; i++) {

            if (possible((*arr_list)[i],pattern,count,arr)) {

                table_add(new_table,(*arr_list)[i],table_get(table,(*arr_list)[i]));
            }


        }

        destroy_list_arr(arr_list,size);

    }

    list_t ** temp = table->tab;
    table->tab = new_table->tab;
    new_table->tab = temp;
    table_destroy(new_table);
    free(count);
    free(arr);

}


void best_guess(table_t * table_dico, table_t * table_proposable,int taille){


    int ** val_arr;
    gen_val_array(&val_arr, taille);
    char best[30];
    double max_E;
    int size_dico;
    char *** all_words_dico = all_words(table_dico,&size_dico);
    int size_prop;
    char *** all_words_prop = all_words(table_proposable,&size_prop);
    printf("Nb de possibilités restantes : %d/%d\n",size_prop,size_dico);

    for(int indice = 0; indice < size_dico; indice ++) {

        char * mot = (*all_words_dico)[indice];
        pattern_t *** pattern_arr = generate_all_pattern(mot,val_arr);
        pattern_t * pattern;
        double E = 0;
        double somme_p = 0;
        for(int j = 0; j<(int)pow(3,taille); j++ ) {
            double p = 0;
            pattern =  (*pattern_arr)[j];

            if (pattern != NULL) {
                p = calculate_proba(pattern,table_proposable,all_words_prop,size_prop);
                if (p != 0) { 
                    E += p*log2(1/p);
                    }
                somme_p += p;
            }
        }       
        
        if (E > max_E) {

            max_E = E;
            strcpy(best,mot);

        }
        printf("Mot '%s' analysé, E = %f, +p = %f // %d/%d\n",mot,E,somme_p,indice+1,size_dico);
        if (somme_p > 1.5 ) { printf("%s,%f\n",mot,somme_p);}
        destroy_pattern_arr(pattern_arr);
        

    }

    destroy_all_words(all_words_dico,size_dico);
    destroy_all_words(all_words_prop,size_prop);
    destroy_val_array(&val_arr,taille);
    printf("Best guess : %s, E = %f\n",best,max_E);

}
