#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "open_dict.h"

int findalphabetposition(char c);
double ** letterfreq(int taillemot, char ** arr, int nombremot);
void printfreq(double ** freq, int taillemot);
double * getmaxfreq(double ** freq, int taillemot);
double* wordscore(double ** freq, char ** possibleword, int taillemot, int nombremot);
char * bestword(char ** possibleword, int taillemot, int nombremot, double* scores);
