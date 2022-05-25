#ifndef Y_WORDLIST_H
#define Y_WORDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "letter.h"
#include "word.h"
#include "table.h"

typedef struct wordlist {
	word_t ** words;
	int size;
} wordlist_t ;


wordlist_t * wordlist_create();
void wordlist_add(wordlist_t * wl, char * word);
void wordlist_open_file(wordlist_t * wl, char * filename, int size);
void wordlist_remove(wordlist_t * wl, int index);
void wordlist_remove_words(wordlist_t *wl, char * guess, char * response);
word_t * wordlist_pick_random_word(wordlist_t * wl);
void wordlist_destroy(wordlist_t * wl);

int check_right_letters(table_t * all_letters, char * word);
int check_miss_placed_letters(table_t * all_letters, char * word);
int check_wrong_letters(table_t * all_letters, char * word);

#endif // Y_WORDLIST_H