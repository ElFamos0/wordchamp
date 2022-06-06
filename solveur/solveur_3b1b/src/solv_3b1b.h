#ifndef solv_3b1b
#define solv_3b1b

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "open_dict.h"
#include <stdbool.h>
#include "table.h"
#include "list.h"
#include "dico.h"

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
void best_guess(table_t * table_dico, table_t * table_proposable,int taille);

char *** all_words(table_t * table, int * size_ptr);
void destroy_all_words(char *** arr, int size);

void val_array_based_on_soluce(char * guess, char * soluce, int ** pattern);
bool is_char_in_string(char c, char * string);
int is_pattern_seen(long ** seen_pattern, long pattern, int size);


// A faire avec structure appropriée



char * best_guess_v2(table_t * table_dico, table_t * table_proposable,int taille,char *** all_words_dico, int size_dico,char *** all_words_prop, int size_prop);
char * best_guess_v3(table_t * table_dico, table_t * table_proposable,int taille,char *** all_words_dico, int size_dico,char *** all_words_prop, int size_prop);
// Puis faire une fonction main pour créer l'intéraction avec le joueur.
// Ensuite, pistes d'optimisation à explorer.

void open_firstguess(char *** array, int * size_ptr, int taille_mot, char * filename);



#endif 