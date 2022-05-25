#ifndef Y_LETTER_H
#define Y_LETTER_H

#include <stdlib.h>

typedef struct letter {
    int count;
    int ** places;
    int size;
} letter_t ;

letter_t * letter_create();
void letter_destroy(letter_t * letter);
void letter_add_place(letter_t * letter, int place, char state);
int letter_is_miss_placed(letter_t * letter, int place);
int letter_is_right(letter_t * letter, int place);
int letter_has_right(letter_t * letter);
int letter_has_miss_place(letter_t * letter);
int letter_has_wrong(letter_t * letter);
int letter_get_count(letter_t * letter);

#endif