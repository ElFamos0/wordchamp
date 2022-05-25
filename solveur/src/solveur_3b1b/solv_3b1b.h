#ifndef solv_3b1b
#define solv_3b1b

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../open_dict.h"
#include <stdbool.h>
#include "hash_table/table.h"
#include "hash_table/list.h"
#include "hash_table/dico.h"

typedef struct pattern_t {

    int * val;
    char * guess; 

} pattern_t;

pattern_t * create_pattern(int * val, char * guess);
void destroy_pattern(pattern_t * result);
bool possible(char * word, pattern_t * result, int * count_arr, bool * bool_arr);
void possible_pre(int ** count_arr, bool ** bool_arr, pattern_t * result);
int count_occ(char * string, char c);
void print_pattern(pattern_t * pattern);
bool pattern_is_possible(pattern_t * pattern);
pattern_t *** generate_all_pattern(char * word,int ** val_arr);
void destroy_pattern_arr(pattern_t *** pattern_arr );
void gen_val_array(int *** val_arr, int size);
void destroy_val_array(int *** val_arr, int size);
void update_possible_words(table_t * table, pattern_t * pattern);
double calculate_proba(pattern_t * pattern, table_t  * table, char *** all_words_arr,int arr_size);

char *** all_words(table_t * table, int * size_ptr);
void destroy_all_words(char *** arr, int size);

// A faire avec structure appropriée


void best_guess(table_t * table_dico, table_t * table_proposable,int taille);

// Puis faire une fonction main pour créer l'intéraction avec le joueur.
// Ensuite, pistes d'optimisation à explorer.


#endif 