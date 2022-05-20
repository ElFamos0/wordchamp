#include "freqsolve.h"

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

double ** letterfreq(int taillemot, char ** arr, int nombremot){
    // calcul des fréquences de chaque lettre pour les mots disponibles
    
    // initialisation de notre array de fréquence en fonction de la taille de mot 
    double ** freq = malloc(sizeof(double *) * 26);
    for(int i = 0; i < 26; i++){
        freq[i] = malloc(sizeof(double) * taillemot);
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

    // si vous voulez voir la fréquence décommenter cette ligne

    //printfreq(freq, taillemot);
    return freq;
}

void printfreq(double ** freq, int taillemot){
    // affichage des fréquences de chaque lettre pour les mots disponibles
    for(int i = 0; i < 26; i++){
        printf("%c : ", ALPHABET[i]);
        for(int j = 0; j < taillemot; j++){
            printf("%f ", freq[i][j]);
        }
        printf("\n");
    }
}



int findalphabetposition(char c){
    // renvoie la position de la lettre dans l'alphabet
    int i = 0;
    while(ALPHABET[i] != c){
        i++;
    }
    return i;
}


double* wordscore(double ** freq, char ** possibleword, int taillemot, int nombremot){
    // renvoie le score du mot en fonction de la fréquence de chaque lettre
    double* scores = malloc(sizeof(double) * nombremot);
    double* maxfreq = getmaxfreq(freq, taillemot);
    for(int i = 0; i < nombremot; i++){
        scores[i] = 1;
        char * mot = possibleword[i];
        for(int j = 0; j < taillemot; j++){
            char c = mot[j];
            scores[i] *= (1 + pow(freq[findalphabetposition(c)][j]-maxfreq[j],2));
        }
    }
    free(maxfreq);
    return scores;
}


char * bestword(char ** possibleword, int taillemot, int nombremot, double* scores){
    // renvoie le meilleur mot en fonction de son score
    char * bestword = malloc(sizeof(char) * (taillemot+1));
    int max = 0;
    for(int i = 1; i < nombremot; i++){
        if(scores[i] < scores[max]){
            max = i;
        }
    }
    strcpy(bestword, possibleword[max]);
    return bestword;
}

double * getmaxfreq(double ** freq, int taillemot){
    // renvoie le tableau des fréquences maximales pour chaque lettre
    double * maxfreq = malloc(sizeof(double) * taillemot);
    for(int i = 0; i < taillemot; i++){
        maxfreq[i] = freq[0][i];
        for(int j = 1; j < 26; j++){
            if(freq[j][i] > maxfreq[i]){
                maxfreq[i] = freq[j][i];
            }
        }
    }
    // display de max freq    
    //for(int i = 0; i < taillemot; i++){
    //    printf("%f ", maxfreq[i]);
    //}
    //printf("\n");
    return maxfreq;
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
    char *reponse= malloc(sizeof(char) * (26));
    char **possibleword = opendict_size(argv[1],taillemot, &nombremot);
    printf("Bienvenue sur le solveur de wordre par fréquence.\n");
    printf("Calcul du meilleur mot en cours ... \n");
    double** freq = letterfreq(taillemot, possibleword, nombremot); //tableau de fréquence des lettres
    double* scores = wordscore(freq, possibleword, taillemot, nombremot); //tableau des scores des mots
    char * bestmot = bestword(possibleword, taillemot, nombremot, scores); //meilleur mot
    printf("Le meilleur mot pour commencer est %s\n", bestmot);
    
    char * reponseattendu= "22222";
    while(strcmp(reponse,reponseattendu)!=0 && strcmp(reponse,"-1")!=0){
        scanf("%s", reponse); // je sais que c'est vulnérable je sais pas comment faire mieux pour le moment
        }
    if(strcmp(reponse,reponseattendu)==0){
        printf("Bravo vous avez gagné !\n");
    }
    else{
        printf("Bye Bye\n");
    }





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

    // free scores
    free(scores);
    //free(bestmot);
    free(bestmot);
    free(reponse);
    return 0;
}