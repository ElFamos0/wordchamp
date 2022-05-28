#include "letter.h"

letter_t * letter_create() {
    letter_t * letter = malloc(sizeof(letter_t));
    letter->count = 0;
    letter->size = 0;
    letter->places = NULL;
    return letter;
}

void letter_destroy(letter_t * letter) {
    if (letter->places != NULL) {
        for (int i = 0; i < letter->size; i++) {
            free(letter->places[i]);
        }
        free(letter->places);
    }
    free(letter);
}

void letter_add_place(letter_t * letter, int place, char state) {
    if (letter->size == 0) {
        letter->size = place + 1 ;
        letter->places = calloc(place + 1, sizeof(int*));
        for (int i = 0; i < place + 1; i++) {
            letter->places[i] = calloc(1, sizeof(int));
            *letter->places[i] = -1;
        }
    } else if (letter->size <= place) {
        letter->places = realloc(letter->places, sizeof(int*)*(place + 1));
        for (int i = letter->size; i <= place; i++) {
            letter->places[i] = calloc(1, sizeof(int));
            *letter->places[i] = -1;
        }
        letter->size = place + 1;
    }
    switch (state) {
        case '1':
            *letter->places[place] = 1;
            break;
        case '2':
            *letter->places[place] = 2;
            break;
        case '0':
            *letter->places[place] = 0;
            break;
    }
}

int letter_is_miss_placed(letter_t * letter, int place) {
    if (letter->size <= place) {
        return 0;
    }
    return *letter->places[place] == 1 ? 1 : 0;
}

int letter_is_right(letter_t * letter, int place) {
    if (letter->size <= place) {
        return 0;
    }
    return *letter->places[place] == 2 ? 1 : 0;
}

int letter_has_right(letter_t * letter) {
    for (int i = 0; i < letter->size; i++) {
        if (*letter->places[i] == 2) {
            return 1;
        }
    }
    return 0;
}

int letter_has_miss_place(letter_t * letter) {
    for (int i = 0; i < letter->size; i++) {
        if (*letter->places[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int letter_has_wrong(letter_t * letter) {
    for (int i = 0; i < letter->size; i++) {
        if (*letter->places[i] == 0) {
            return 1;
        }
    }
    return 0;
}

int letter_get_count(letter_t * letter) {
    int c = 0;
    for (int i = 0; i < letter->size; i++) {
        if (*letter->places[i] > 0) {
            c++;
        }
    }
    return c;
}