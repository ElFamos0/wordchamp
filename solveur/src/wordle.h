#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "open_dict.h"

enum {
    WIN,
    LOSE,
    NUMBEROFLETTER,
    NUMBEROFGUESS,
    ALLCLEAR
} typedef errormessage;


void destroy_array(char ** array, int n);

void printerrormessage(errormessage error,char * one_str);