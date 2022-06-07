#ifndef naif_h
#define naif_h
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "strInt.h"
#include "linked_list.h"


linked_list_t* generateList();
void extractList(linked_list_t*, int, char**, int, strInt_t*, int, strInt_t*);

#endif