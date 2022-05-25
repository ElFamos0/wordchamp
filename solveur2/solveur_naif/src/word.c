#include "word.h"

word_t * word_create(char * word) {
    word_t * w = malloc(sizeof(word_t));
    w->word = strdup(word);
    w->score = 1;
    return w;
}

void word_destroy(word_t * w) {
    free(w->word);
    free(w);
}

int word_has(char * word, char letter) {
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        if (word[i] == letter) {
            return 1;
        }
    }
    return 0;
}

int word_count(char * word, char letter) {
    int n = strlen(word);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (word[i] == letter) {
            count++;
        }
    }
    return count;
}