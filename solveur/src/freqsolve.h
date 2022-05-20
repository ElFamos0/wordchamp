#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "open_dict.h"

int findalphabetposition(char c);
float ** letterfreq(int taillemot, char ** arr, int nombremot);
void printfreq(float ** freq, int taillemot);
float wordscore(char * word, float ** freq, int taillemot);
float * getmaxfreq(float ** freq, int taillemot);

