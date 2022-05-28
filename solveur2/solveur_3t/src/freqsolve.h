#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "open_dict.h"
#include "linked_list.h"

#define DICT_FILE "dicoz.txt"
#define DEFAULT_WORD_LENGTH 5

int findalphabetposition(char c);
double ** letterfreq(int taillemot, char ** arr, int nombremot);
void printfreq(double ** freq, int taillemot);
double * getmaxfreq(double ** freq, int taillemot);
double* wordscore(double ** freq, char ** possibleword, int taillemot, int nombremot);
char * bestword(char ** possibleword, int taillemot, int nombremot, double* scores);
char * badletter(char * guess, char * reponse, int taillemot);
char* misplaceletter(char* guess, char* reponse, int taillemot);
char* goodletter(char* guess, char* reponse, int taillemot);
char ** wordremover(char ** possibleword,char* reponse,char* bestmot,int taillemot,int nombremot, int* nombremot2);
int* goodarray(char* guess, char* reponse, int taillemot);
int* misplacearray(char* guess, char* reponse, int taillemot);
int countchar(char * word, char letter);

