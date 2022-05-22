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

char * badletter(char * guess, char * reponse, int taillemot){
    char * badletterlist = malloc(sizeof(char) * (taillemot+1));
    int place = 0;
    for(int i = 0; i < taillemot; i++){
        if(reponse[i] == '0'){
            badletterlist[place] = guess[i];
            place++;
    }
    }
    badletterlist[place] = '\0';
    return badletterlist;
}

char* misplaceletter(char* guess, char* reponse, int taillemot){
    char* misplaceletterlist = malloc(sizeof(char) * (taillemot+1));
    int place = 0;
    for(int i = 0; i < taillemot; i++){
        if(reponse[i] == '1'){
            misplaceletterlist[place] = guess[i];
            place++;
        }

    }
    misplaceletterlist[place] = '\0';
    return misplaceletterlist;
}

int* misplacearray(char* guess, char* reponse, int taillemot){
    int* misplacepositionlist = malloc(sizeof(int) * (taillemot+1));
    int place = 0;
    for(int i = 0; i < taillemot; i++){
        if(reponse[i] == '1'){
            misplacepositionlist[place] = i;
            place++;
        }

    }
    return misplacepositionlist;
}
char* goodletter(char* guess, char* reponse, int taillemot){
    char* goodletterlist = malloc(sizeof(char) * (taillemot+1));
    int place = 0;
    for(int i = 0; i < taillemot; i++){
        if(reponse[i] == '2'){
            goodletterlist[place] = guess[i];
            place++;
        }
    }
    goodletterlist[place] = '\0';
    return goodletterlist;
}

int* goodarray(char* guess, char* reponse, int taillemot){
    int* goodpositionlist = malloc(sizeof(int) * (taillemot+1));
    int place = 0;
    for(int i = 0; i < taillemot; i++){
        if(reponse[i] == '2'){
            goodpositionlist[place] = i;
            place++;
        }

    }
    return goodpositionlist;
}

char** wordremover(char ** possibleword,char* reponse,char* bestmot,int taillemot,int nombremot, int * nombremot2){
    // on parcourt tous les mots disponibles et on met a NULL les mots qui ne correspondent pas à la réponse
    char * badletterlist = badletter(bestmot, reponse, taillemot);
    char * misplaceletterlist = misplaceletter(bestmot, reponse, taillemot);
    char * goodletterlist = goodletter(bestmot,reponse , taillemot);
    char * existantletterlist = malloc(sizeof(char) * (taillemot+1)*2);
    strcpy(existantletterlist, goodletterlist);
    strcat(existantletterlist, misplaceletterlist);

    int * misplacepositionlist = misplacearray(bestmot, reponse, taillemot);
    int * goodpositionlist = goodarray(bestmot, reponse, taillemot);
    
    char ** newpossibleword = malloc(sizeof(char *) * (nombremot));
    
    printf("%s - %d\n", badletterlist, strlen(badletterlist));
    printf("%s - %d\n", misplaceletterlist, strlen(misplaceletterlist));
    printf("%s - %d\n", goodletterlist, strlen(goodletterlist));
    printf("%s - %d\n", existantletterlist, strlen(existantletterlist));
    /*
    for(int i =0;i<strlen(misplaceletterlist);i++){
        printf("%d\n", misplacepositionlist[i]);
    }
    for(int i =0;i<strlen(goodletterlist);i++){
        printf("%d\n", goodpositionlist[i]);
    }
    */

    // premier filtre DONE 
    int compteur = 0;
    int check = 0;
    for(int i = 0; i < nombremot; i++){
        check = 0;
        for(int j=0; j<strlen(badletterlist);j++){
            if(strchr(possibleword[i],badletterlist[j]) != NULL){
                if((strchr(misplaceletterlist,badletterlist[j]) != NULL) || (strchr(goodletterlist,badletterlist[j]) != NULL)){
                    check = 0;
                }
                else{
                    check = 1;
                }
            }
        }
        if(check == 0){
            newpossibleword[compteur] = malloc(sizeof(char) * (taillemot+1));
            strcpy(newpossibleword[compteur], possibleword[i]);
            compteur++;
        }
    }
    printf("COMPTEUR MOT RESTANT filtre 1 %d\n",compteur);

    for(int i = 0; i < nombremot; i++){
        free(possibleword[i]);
    }
    free(possibleword);

    // deuxième filtre 
    char ** newpossibleword2 = malloc(sizeof(char *) * (compteur));

    int compteur2 = 0;
    for(int i = 0; i<compteur;i++){
        check = 0;
        for(int j=0; j<strlen(goodletterlist);j++){
            if(newpossibleword[i][goodpositionlist[j]] != goodletterlist[j]){
                check = 1;
            }
        }
        if(check == 0){
            newpossibleword2[compteur2] = malloc(sizeof(char) * (taillemot+1));
            strcpy(newpossibleword2[compteur2], newpossibleword[i]);
            compteur2++;
        }
    }
    printf("COMPTEUR MOT RESTANT filtre 2 %d\n",compteur2);
    /*
    for(int i=0;i<compteur2;i++){
        printf("%s\n",newpossibleword2[i]);
    } 
        */
    for(int i = 0; i < compteur; i++){
        free(newpossibleword[i]);
    }
    free(newpossibleword);


    // troisième filtre
    char ** newpossibleword3 = malloc(sizeof(char *) * (compteur2));
    int compteur3 = 0;
    for(int i = 0; i<compteur2;i++){
        check = 0;
        for(int j=0; j<strlen(misplaceletterlist);j++){
            if(newpossibleword2[i][misplacepositionlist[j]] == misplaceletterlist[j]){
                check = 1;
            }
        }
        if(check == 0){
            newpossibleword3[compteur3] = malloc(sizeof(char) * (taillemot+1));
            strcpy(newpossibleword3[compteur3], newpossibleword2[i]);
            compteur3++;
        }
    }
    printf("COMPTEUR MOT RESTANT filtre 3 %d\n",compteur3);
    /*
    for(int i=0;i<compteur3;i++){
        printf("%s\n",newpossibleword3[i]);
    }
    */  
    for(int i = 0; i < compteur2; i++){
        free(newpossibleword2[i]);
    }
    free(newpossibleword2);


    char ** newpossibleword4 = malloc(sizeof(char *) * (compteur3));
    int compteur4 = 0;
    for(int i = 0; i<compteur3;i++){
        check = 0;
        for(int j=0; j<strlen(existantletterlist);j++){
            if(strchr(newpossibleword3[i],existantletterlist[j]) == NULL){
                check = 1;
            }
        }
        if(check == 0){
            newpossibleword4[compteur4] = malloc(sizeof(char) * (taillemot+1));
            strcpy(newpossibleword4[compteur4], newpossibleword3[i]);
            compteur4++;
        }
    }




    printf("COMPTEUR MOT RESTANT filtre 4 %d\n",compteur4);
    /*
    for(int i=0;i<compteur4;i++){
        printf("%s\n",newpossibleword4[i]);
    }
    */
    
    for(int i = 0; i < compteur3; i++){
        free(newpossibleword3[i]);
    }
    free(newpossibleword3);

    char** newpossibleword5 = malloc(sizeof(char *) * (compteur4));
    int compteur5 = 0;
    for(int i = 0; i<compteur4;i++){
        check = 0;
        for(int j=0; j<strlen(badletterlist);j++){
            if(strchr(newpossibleword4[i],badletterlist[j]) != NULL && strchr(newpossibleword4[i],existantletterlist[j]) != NULL){
                if (countchar(newpossibleword4[i],badletterlist[j]) != countchar(existantletterlist,badletterlist[j])){
                    check = 1;
                }
            }

        }
        if(check == 0){
            newpossibleword5[compteur5] = malloc(sizeof(char) * (taillemot+1));
            strcpy(newpossibleword5[compteur5], newpossibleword4[i]);
            compteur5++;
        }
    }



    printf("COMPTEUR MOT RESTANT filtre 5 %d\n",compteur5);
    
    /*for(int i=0;i<compteur5;i++){
        printf("%s\n",newpossibleword5[i]);
    }
    */
    for(int i = 0; i < compteur4; i++){
        free(newpossibleword4[i]);
    }
    free(newpossibleword4);

    
    *nombremot2 = compteur5;

    free(badletterlist);
    free(goodletterlist);
    free(misplaceletterlist);
    free(goodpositionlist);
    free(misplacepositionlist);
    free(existantletterlist);

    return newpossibleword5;
}

int countchar(char * word, char letter){
    int count = 0;
    for(int i=0;i<strlen(word);i++){
        if(word[i] == letter){
            count++;
        }
    }
    return count;
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
    int i = 0;
    char reponseattendu[taillemot+1];
    for (i = 0; i < taillemot; i++){
        reponseattendu[i] = '2';
    }
    reponseattendu[taillemot] = '\0';
    while(1){
        scanf("%s", reponse); // je sais que c'est vulnérable je sais pas comment faire mieux pour le moment
        if (strcmp(reponse, "-1") == 0){
            printf("Vous avez choisi de quitter le solveur\n");
            break;
        }
        if(strcmp(reponse, reponseattendu) == 0){
            printf("Bravo vous avez trouvé le mot %s\n", bestmot);
            break;
        }
        if (strlen(reponse) != taillemot){
            printf("Vous avez saisi un mot de taille incorrecte\n");
            continue;
        }
        printf("Vous avez saisi %s\n", reponse);
        possibleword = wordremover(possibleword, reponse, bestmot, taillemot, nombremot, &nombremot);
        printf("Il reste %d mots possibles\n", nombremot);
        printf("[");
        for(int i = 0; i < nombremot; i++){
            printf("%s,", possibleword[i]);
        }
        printf("]\n");
        free(scores);
        for(int i = 0; i < 26; i++){
            free(freq[i]);
        }
        free(freq);
        free(bestmot);

        freq = letterfreq(taillemot, possibleword, nombremot);
        scores = wordscore(freq, possibleword, taillemot, nombremot);
        bestmot = bestword(possibleword, taillemot, nombremot, scores);


        printf("Le meilleur mot pour continuer est %s\n", bestmot);
        }
    //free possible word
    for(int i = 0; i < nombremot; i++){
        free(possibleword[i]);
    }
    free(possibleword);

    free(reponse);
    //free freq
    for(int i = 0; i < 26; i++){
        free(freq[i]);
    }
    free(freq);

    // free scores
    free(scores);
    //free(bestmot);
    free(bestmot);
    return 0;
}