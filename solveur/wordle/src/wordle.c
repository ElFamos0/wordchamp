#include "wordle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "open_dict.h"
#include <unistd.h>

int main(int argc, char *argv[]){
    // interactive wordle game
    // read the dictionary file
    if (argc != 3) {
        printf("Usage: ./wordle <dictionary file> <number of letter>\n");
        return 1;
    }

    int n;
    char ** array = opendict_size(argv[1], atoi(argv[2]),&n);
    if (n==0){
        printf("Error: no word in the dictionary file\n");
        return 1;
    }
    // select a random word and print int
    printf("\e[1;1H\e[2J");
    srand(time(NULL));
    int random = rand() % n;
    printf("%s\n", array[random]);
    
    // si vous souhaitez faire un test forcé : 
    //strcpy(array[random], "AIGLE");



    int length = strlen(array[random]);
    int win = 0;

    // ask the user to guess the word
    char * guess = malloc(sizeof(char)*26);
    char * guess_array[6];
    char * guess_made[6];

    for (int i = 0; i < 6; i++) {
        guess_array[i] = (char*) calloc(26, sizeof(char));
        guess_made[i] = (char*) calloc(26, sizeof(char));
        for(int j = 0; j < length; j++){
            guess_array[i][j] = '0';    // initialize the guess array with '0'
        }
    }
 // clear the screen

    int i = 0;  // i is the number of tries
    errormessage message = ALLCLEAR;
    while (1){
        printf("\e[1;1H\e[2J");
        printf("VOUS JOUEZ AVEC UN MOT DE %d LETTRES\n", length);
        for(int i = 0; i<6; i++){
            for(int j = 0; j<length; j++){
                if(guess_array[i][j] == '0'){
                    printf("⬛");
                }
                if(guess_array[i][j] == '1'){
                    printf("🟨");
                }
                if(guess_array[i][j] == '2'){
                    printf("🟥");
                }
            }
            printf("  %s\n" , guess_made[i]);
        }
        printerrormessage(message, array[random]);
        if (win==1){
            break;
        }
        printf("ESSAI N° %d : \n", i+1);
        fgets(guess, 26, stdin);
        guess[strlen(guess)-1] = '\0';

        if (strlen(guess) == strlen(array[random])){
            if (strcmp(guess, array[random]) == 0){
                for (int j = 0; j<length; j++){
                guess_array[i][j] = '2';}
                strcpy(guess_made[i], guess);
                message = WIN;
                win = 1;
                free(guess);
            }
            else {
                if (i<=5){
                    char * copie = malloc(sizeof(char)*26);
                    char * solution = malloc(sizeof(char)*26);
                    strcpy(copie, guess);
                    strcpy(solution, array[random]);
                    for (int j = 0; j<length; j++){
                        if (copie[j] == array[random][j]){
                            guess_array[i][j] = '2';
                            copie[j] = '_';
                            solution[j] = '#';
                        }
                    }
                    for (int j = 0; j<length; j++){
                        if (strchr(solution,copie[j]) != NULL){ // if the character is in the solution
                            guess_array[i][j] = '1';
                            for (int k = 0; k<length; k++){
                                if (copie[j] == solution[k]){
                                    solution[k] = '#';
                                    break;
                                }
                            }
                            copie[j] = '_';
                        }
                        }

                    strcpy(guess_made[i], guess);
                    *guess = '\0';
                    message = ALLCLEAR;
                    i++;
                    free(copie);
                    free(solution);
                    if (i==6){
                        message = LOSE;
                        free(guess);
                        win = 1;
                    }
                }
                else{
                    message = LOSE;
                    free(guess);
                    win = 1;
                }
            }
        }
        else {
            message = NUMBEROFLETTER;
            printf("strlen(guess) = %d\n", strlen(guess));
        }
    }
    destroy_array(array, n);
    for (int i = 0; i < 6; i++) {
        free(guess_array[i]);
        free(guess_made[i]);
    } 
}


void destroy_array(char ** array, int n) {
    for (int i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
}

void printerrormessage(errormessage error, char * soluce) {
    switch (error) {
        case WIN:
            printf("Bravo ! Vous avez gagné !\n");
            break;
        case LOSE:
            printf("Vous avez perdu !\n");
            printf("%s\n", soluce);
            break;
        case NUMBEROFLETTER:
            printf("MAUVAISE LONGUEUR DE MOT\n");
            break;
        case NUMBEROFGUESS:
            printf("BARRE DE WORDLE\n");
            break;
        case ALLCLEAR:
            break;
        default:
            break;
    }
}
