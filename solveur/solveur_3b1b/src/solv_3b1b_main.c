#include "solv_3b1b.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "open_dict.h"

int main(int argc, char *argv[]) {
    
    int taille_mot = openwsolf();

    char * filename = "dicoz.txt";

    table_t * table_dico = dico_load_size(filename,taille_mot);
    table_t * table_prop = dico_load_size(filename,taille_mot);
    int size_dico;
    char ** all_words_dico;
    all_words_dico = opendict_size(filename,taille_mot,&size_dico);

    int size_prop;
    char ** all_words_prop;
    all_words_prop = opendict_size(filename,taille_mot,&size_prop);

    char ** arr_first_guess;
    int size = 0;
    char filename2[] =  "dico_1stguess.txt";
    open_firstguess(&arr_first_guess,&size,taille_mot,filename2);
    char * best_mot = malloc(sizeof(char) * (26));
    bool state = true;

    for(int i = 0; i< size; i++) {

        if (table_contains(table_dico,arr_first_guess[i]) && state) {strcpy(best_mot,arr_first_guess[i]); state = false;}
        
        free(arr_first_guess[i]);

    }
    printf("%s\n",best_mot);
    int number_of_guess = 1;
    char *reponse = malloc(sizeof(char) * (30));
    char reponseattendu[taille_mot+1];
    for (int i = 0; i < taille_mot; i++){
        reponseattendu[i] = '2';
    }
    reponseattendu[taille_mot] = '\0';
    int val[taille_mot];
    memset(val,0,taille_mot*sizeof(int));
    

    while(1) {

        fgets (reponse, 30, stdin);
        reponse = strtok(reponse, "\n");
        char * mot_propose;
        //printf("Réponse: %s\n",reponse);

        if (strcmp(reponse, "-1") == 0){
            //printf("Vous avez choisi de quitter le solveur\n");
            break;
        }
        if(strcmp(reponse, reponseattendu) == 0){
            //printf("Bravo vous avez trouvé le mot %s\n", bestmot);
            break;
        }
        if (strlen(reponse) != taille_mot){
            //printf("Vous avez saisi un mot de taille incorrecte %d\n", taillemot);
            continue;
        }
        else {

            int i = 0;
            while(isdigit(reponse[i])) {
                val[i] = reponse[i] - '0';
                i++;
            }
            pattern_t * pattern = create_pattern(val,best_mot);
            //print_pattern(pattern);

            update_possible_words(table_prop,pattern);

            if (number_of_guess == 1) {
                for (int i = 0; i<size_prop;i++) {
                    free(all_words_prop[i]);
                }
                free(all_words_prop);
            }
            
            int size_prop = 0;
            char *** all_words_prop;
            all_words_prop = all_words(table_prop,&size_prop);

            if (size_prop == 0) {
                printf("Aucun mot valide, fin du programme\n");
                destroy_pattern(pattern);
                destroy_all_words(all_words_prop,size_prop);
                break;
            }
            

            // for(int i = 0; i< size_prop;i++) {

            //     printf("%s\n",(*all_words_prop)[i]);
            // }

            if(taille_mot > 5) {
                mot_propose = best_guess_v3(table_dico,table_prop,taille_mot,&all_words_dico,size_dico,all_words_prop,size_prop);
            }
            else {
                mot_propose = best_guess_v2(table_dico,table_prop,taille_mot,&all_words_dico,size_dico,all_words_prop,size_prop);
            }

            strcpy(best_mot,mot_propose);
            free(mot_propose);
            printf("%s\n",best_mot);
            number_of_guess++;

            destroy_pattern(pattern);
            destroy_all_words(all_words_prop,size_prop);
        }
    }


    // Freeing all allocated memory

    free(arr_first_guess);
    free(reponse);
    free(best_mot);
    table_destroy(table_dico);
    table_destroy(table_prop);
    for (int i = 0; i<size_dico;i++) {
        free(all_words_dico[i]);

    }
    free(all_words_dico);


    return 0;
}