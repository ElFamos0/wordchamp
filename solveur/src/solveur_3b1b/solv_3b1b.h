#ifndef solv_3b1b
#define solv_3b1b

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../open_dict.h"
#include <stdbool.h>

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
pattern_t *** generate_all_pattern(char * word,int ** val_arr);
void destroy_pattern_arr(pattern_t *** pattern_arr );
void gen_val_array(int *** val_arr, int size);
void destroy_val_array(int *** val_arr, int size);

// A faire avec structure appropriée

double calculate_proba(pattern_t * pattern, char ** liste_mot);
void update_possible_words(char ** liste_mot, pattern_t * pattern);
char * best_guess(char ** liste_mot, char ** mots_proposables);

// Puis faire une fonction main pour créer l'intéraction avec le joueur.
// Ensuite, pistes d'optimisation à explorer.


#endif 