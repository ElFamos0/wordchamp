#include "freqsolve.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

float ** letterfreq(int taillemot, char ** arr, int nombremot){
    // calcul des fréquences de chaque lettre pour les mots disponibles
    
    // initialisation de notre array de fréquence en fonction de la taille de mot 
    float ** freq = malloc(sizeof(float *) * 26);
    for(int i = 0; i < 26; i++){
        freq[i] = malloc(sizeof(float) * taillemot);
    }
    // on initialise les fréquences à 0
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < taillemot; j++){
            freq[i][j] = 0;
        }
    }

    // on parcourt tous les mots disponibles et on ajoute 1 à la fréquence de chaque lettre

    for(int i = 0; i<nombremot; i++){
        for(int j = 0; j<strlen(arr[i]); j++){
            freq[findalphabetposition(arr[i][j])][j] += 1;
        }
    }
    // print freq
    for(int i = 0; i < 26; i++){
        printf("%c : ", ALPHABET[i]);
        for(int j = 0; j < taillemot; j++){
            printf("%f ", freq[i][j]);
        }
        printf("\n");
    }
    return freq;
}

int findalphabetposition(char c){
    // renvoie la position de la lettre dans l'alphabet
    int i = 0;
    while(ALPHABET[i] != c){
        i++;
    }
    return i;
}


int main(int argc, char *argv[]) {
    int nombremot;
    if(argc != 3){
        printf("Usage: ./freqsolve <file> <wordsize>\n");
        return 1;
    }
    int taillemot;
    taillemot = atoi(argv[2]);
    if (taillemot < 1 || taillemot > 21){
        printf("Vous avez choisi un mot de taille impossible\n");
        return 1;
    }
    char **possibleword = opendict_size(argv[1],taillemot, &nombremot);
    printf("Bienvenue sur le solveur de wordre par fréquence.\n");
    printf("Calcul du meilleur mot en cours ... \n");
    float** freq = letterfreq(taillemot, possibleword, nombremot);


    // NETTOYAGE DU PROGRAMME


    //free possible word
    for(int i = 0; i < nombremot; i++){
        free(possibleword[i]);
    }
    free(possibleword);

    //free freq
    for(int i = 0; i < 26; i++){
        free(freq[i]);
    }
    free(freq);
}