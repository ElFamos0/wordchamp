#include "solv_3b1b.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../open_dict.h"


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

    table_t * new_table = table_create(2000);

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


bool is_char_in_string(char c, char * string) {

    int n = strlen(string) ;

    for (int i = 0; i<n;i++) {

        if (c == string[i]) {return true;}

    }

    return false;
}




void val_array_based_on_soluce(char * guess, char * soluce, int ** pattern) {

    int count_soluce[26];
    int count_guess[26];
    memset(count_soluce, 0, sizeof(int) * 26);
    memset(count_guess, 0, sizeof(int) * 26);
    int n = strlen(guess);

    for(int i = 0; i < n ; i++) {

        count_soluce[soluce[i] - 65] += 1;

        if (soluce[i] == guess[i]) {

            (*pattern)[i] = 2;
            count_guess[guess[i] -65] += 1;
        }
    }

    for(int i = 0; i < n ; i++) {

        if ((*pattern)[i] != 2 && is_char_in_string(guess[i],soluce) && count_guess[guess[i] -65] < count_soluce[guess[i] -65]) {

            (*pattern)[i] = 1;
            count_guess[guess[i] -65] += 1;
        }
    }


}


char * best_guess_v2(table_t * table_dico, table_t * table_proposable,int taille, char *** all_words_dico, int size_dico,char *** all_words_prop, int size_prop){


    char  best[20][30];
    for(int i = 0; i< 20; i++) {

        strcpy(best[i],"");
    }
    double max_E[20];
    memset(max_E, 0.0, sizeof(double) * 20);
    //printf("Nb de possibilités restantes : %d/%d\n",size_prop,size_dico);
    if (size_prop <= 2 && size_prop>0) {
        char * retour = (char*)malloc(taille+1);
        strcpy(retour,(*all_words_prop)[0]);
        return retour;
    }
    else if (size_prop == 0) {
        char * retour = (char*)malloc(taille+1);
        strcpy(retour,"");
        return retour;
        }

    for(int indice = 0; indice < size_dico; indice ++) {

        char * mot_test = (*all_words_dico)[indice];
        double E = 0;
        double somme_p = 0;
        int * p_array = (int *) malloc((int)pow(3,taille) * sizeof(int));
        memset(p_array, 0, sizeof(int) * (int)pow(3,taille));

        for( int j = 0; j< size_prop;j++) {

            char * mot_prop = (*all_words_prop)[j];
            int  * pattern = (int*) malloc(taille*sizeof(int));
            memset(pattern, 0, sizeof(int) * taille);
            val_array_based_on_soluce(mot_test,mot_prop, &pattern);

            int temp = 0;

            for (int i = 0; i < taille; i++) {

                temp += pattern[i] * (int)pow(3,taille-1-i);
            }
            p_array[temp] += 1;
            
            free(pattern);

        }
        double p = 0;
        double size_prop_double = (double) size_prop;
        for( int j = 0; j< (int)pow(3,taille);j++) {

            p = p_array[j] / size_prop_double ;
            if (p != 0) { 
                    E += p*log2(1/p);
                    }
            somme_p += p;          
        }

        int i = 0;
        while(i<20 && max_E[i] > E) {
            i++;
        }
        
        //printf("Mot '%s' analysé, E = %f, +p = %f // %d/%d\n",mot_test,E,somme_p,indice+1,size_dico);
        free(p_array);

        char * mot_cpy =(char*)malloc((strlen(mot_test)+1)*sizeof(char));
        strcpy(mot_cpy,mot_test);

        if (i < 20) {
            char temp_str[30]; 
            double temp_val;

            while(i<20) {

                strcpy(temp_str,best[i]);
                double temp_val = max_E[i];
                max_E[i] = E;
                strcpy(best[i],mot_cpy);
                E = temp_val;
                strcpy(mot_cpy,temp_str);
                i++;
            }
        }
        free(mot_cpy);
    }

    // for(int i = 0; i<20; i++) {
    //     printf("Best guess %d : %s, E = %f\n",i+1,best[i],max_E[i]);

    // }

    char * retour = (char*)malloc(taille+1);
    strcpy(retour,best[0]);
    return retour;
}

int is_pattern_seen(long ** seen_pattern, long pattern, int size) {

    for(int i = 0; i< size; i++) {
        if (pattern == (*seen_pattern)[i]) {
            return i;}

    }
    return -1;

}


char * best_guess_v3(table_t * table_dico, table_t * table_proposable,int taille, char *** all_words_dico, int size_dico,char *** all_words_prop, int size_prop){


    char  best[20][30];
    for(int i = 0; i< 20; i++) {

        strcpy(best[i],"");
    }
    double max_E[20];
    memset(max_E, 0.0, sizeof(double) * 20);
    //printf("Nb de possibilités restantes : %d/%d\n",size_prop,size_dico);

    if (size_prop <= 2&& size_prop>0) {
        char * retour = (char*)malloc(taille+1);
        strcpy(retour,(*all_words_prop)[0]);
        return retour;
    }
    else if (size_prop == 0) {
        char * retour = (char*)malloc(taille+1);
        strcpy(retour,"");
        return retour;
        }

    for(int indice = 0; indice < size_dico; indice ++) {

        char * mot_test = (*all_words_dico)[indice];
        double E = 0;
        double somme_p = 0;
        int size = 0;
        long * seen_pattern = (long*)malloc(size_prop*sizeof(long));
        memset(seen_pattern,0,size_prop*sizeof(long));
        double * count_pattern = (double*)malloc(size_prop*sizeof(long));
        memset(count_pattern,0.0,size_prop*sizeof(double));

        for( int j = 0; j< size_prop;j++) {

            char * mot_prop = (*all_words_prop)[j];
            int  * pattern = (int*) malloc(taille*sizeof(int));
            memset(pattern, 0, sizeof(int) * taille);
            val_array_based_on_soluce(mot_test,mot_prop, &pattern);
            long temp = 0;
            for (int i = 0; i < taille; i++) {

                temp += pattern[i] * (int)pow(3,taille-1-i);
            }

    
            int p_ind = is_pattern_seen(&seen_pattern,temp,size);
            if (p_ind == -1) {
                size++;
                seen_pattern[size-1] = temp;
                count_pattern[size-1] += 1.0;      
            }
            else {
                count_pattern[p_ind] += 1.0;
                
            }
            
            free(pattern);
        }

        double p = 0;
        double size_prop_double = (double) size_prop;
        for( int j = 0; j< size;j++) {
            
            p = count_pattern[j] / size_prop_double ;
            if (p != 0) { 
                    E += p*log2(1/p);
                    }
            somme_p += p;        
        }
        free(count_pattern);
        free(seen_pattern);
        int i = 0;
        while(i<20 && max_E[i] > E) {
            i++;
        }
        
         //printf("Mot '%s' analysé, E = %f, +p = %f // %d/%d\n",mot_test,E,somme_p,indice+1,size_dico);
        char * mot_cpy =(char*)malloc((strlen(mot_test)+1)*sizeof(char));
        strcpy(mot_cpy,mot_test);

        if (i < 20) {
            char temp_str[30]; 
            double temp_val;

            while(i<20) {

                strcpy(temp_str,best[i]);
                double temp_val = max_E[i];
                max_E[i] = E;
                strcpy(best[i],mot_test);
                E = temp_val;
                strcpy(mot_test,temp_str);
                i++;
            }
        }
        free(mot_cpy);
    }

    // for(int i = 0; i<20; i++) {
    //     printf("Best guess %d : %s, E = %f\n",i+1,best[i],max_E[i]);

    // }
    char * retour = (char*)malloc(taille+1);
    strcpy(retour,best[0]);
    return retour;
}

void open_firstguess(char *** array, int * size_ptr, int taille_mot, char * filename){

    FILE* ptr;
    ptr = fopen(filename, "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    int c = 0;
    char mot[40] = "";
    int taille_l = 0;
    char ligne[500];
    (*array) = (char**)malloc(21*sizeof(char*));
    int size = 0;

    while (fgets(ligne, 500, ptr) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = 0;
        strcpy(mot,"");
        int i = 0;
        while (isdigit(ligne[i])) {
            strncat(mot, &(ligne[i]), 1);
            i++;
        }
        taille_l = atoi(mot);
        i++;
        if (taille_l== taille_mot) {
            strcpy(mot,"");
            while(ligne[i] != '\0') {

                if(ligne[i] == ' ') {
                    (*array)[size] = (char*)malloc((taille_mot*2)*sizeof(char));
                    strcpy((*array)[size],mot);
                    size++;
                    strcpy(mot,"");
                }
                else {
                    strncat(mot, &(ligne[i]), 1);
                }
                i++;
            }
            break;
        } 
    }
    *size_ptr = size;
    fclose(ptr);

}
