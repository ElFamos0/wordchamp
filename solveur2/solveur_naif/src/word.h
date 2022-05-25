#ifndef Y_WORD_H
#define Y_WORD_H

#include <stdlib.h>
#include <string.h>

typedef struct word {
	int	score;
	char * word;
} word_t;

word_t * word_create(char * word);
void word_destroy(word_t * word);

int word_has(char * word, char letter);
int word_count(char * word, char letter);

#endif