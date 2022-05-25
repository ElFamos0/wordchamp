#include "wordlist.h"

wordlist_t * wordlist_create() {
    wordlist_t * wl = malloc(sizeof(wordlist_t));
    wl->size = 0;
    wl->words = NULL;
    return wl;
}

void wordlist_add(wordlist_t * wl, char * word) {
    if (wl->size == 0) {
        wl->words = calloc(1, sizeof(char*));
        wl->words[0] = word_create(word);
        wl->size++;
        return;
    }
    wl->words = realloc(wl->words, sizeof(char*)*(wl->size + 1));
    wl->words[wl->size] = word_create(word);
    wl->size++;
}

void wordlist_open_file(wordlist_t * wl, char * filename, int size) {
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strlen(line) != size+1) {
            continue;
        }
        //We remove the trailing \n
        line[strlen(line)-1] = '\0';
        wordlist_add(wl, line);
    }
    fclose(fp);
    if (line) {
        free(line);
    }
}

void wordlist_destroy(wordlist_t * wl) {
    for (int i = 0; i < wl->size; i++) {
        word_destroy(wl->words[i]);
    }
    free(wl->words);
    free(wl);
}

void wordlist_remove(wordlist_t * wl, int index) {
    word_destroy(wl->words[index]);
    wl->words[index] = wl->words[wl->size - 1];
    wl->size--;
    wl->words = realloc(wl->words, sizeof(char*)*wl->size);
    return;
}

void wordlist_remove_words(wordlist_t * wl, char * guess, char * response) {
    // On vérifie que la taille est bonne
    assert(strlen(guess) == strlen(response));
    int n = strlen(response);

    table_t * counts = table_create(strlen(response));
    for (int i = 0; i < n; i++) {
        char * key = calloc(2, sizeof(char));
        key[0] = guess[i];

        letter_t * l = table_get(counts, key);
        if (l == NULL) {
            l = letter_create();
            table_add(counts, key, l);
        }
        free(key);
    }

    for (int i = 0; i < n; i++) {

        char * key = calloc(2, sizeof(char));
        key[0] = guess[i];
        letter_t * l = table_get(counts, key);

        if (l == NULL) {
            l = letter_create();
            table_add(counts, key, l);
        }
        
        switch (response[i]) {
            case '1':
                letter_add_place(l, i, '1');
                break;
            case '2':
                letter_add_place(l, i, '2');
                break;
            case '0':
                letter_add_place(l, i, '0');
                break;
        }

        free(key);
    }


	int i, j, s;
	for (i=0; i<wl->size; i++) {

        // kick it : wl->words[j]->score = -1;

        // Wrong size words
        if (strlen(wl->words[i]->word) != n) {
            wl->words[i]->score = -1;
            continue;
        }

        // Check right letters
        if (check_right_letters(counts, wl->words[i]->word) == 0) {
            wl->words[i]->score = -1;
            continue;
        }

        // Check miss placed letters
        if (check_miss_placed_letters(counts, wl->words[i]->word) == 0) {
            wl->words[i]->score = -1;
            continue;
        }

        // Check wrong letters
        if (check_wrong_letters(counts, wl->words[i]->word) == 0) {
            wl->words[i]->score = -1;
            continue;
        }

	}

	s = wl->size;

	for (i=0; i<wl->size; ) {
		if (wl->words[i]->score == -1) {
			wordlist_remove(wl, i);
		} else {
			i++;
		}
	}

    void iterator(char * key, void * value) {
        letter_t * l = value;
        letter_destroy(l);
    }
    table_iterate(counts, iterator);

    table_destroy(counts);
}

word_t * wordlist_pick_random_word(wordlist_t * wl) {
    int r = rand() % wl->size;
    return wl->words[r];
}

int check_right_letters(table_t * all_letters, char * word) {
    int c = 1;
    void iterator(char * key, void * value) {
        letter_t * l = value;
        char letter = key[0];
        if (!letter_has_right(l)) {
            return;
        }
        if (!word_has(word, letter)) {
            c = 0;
        }
        for (int i = 0; i < strlen(word); i++) {
            if (!letter_is_right(l, i)) {
                continue;
            }
            if (word[i] != letter) {
                c = 0;
            }
        }
    }
    table_iterate(all_letters, iterator);
    return c;
}

int check_miss_placed_letters(table_t * all_letters, char * word) {
    int c = 1;
    void iterator(char * key, void * value) {
        letter_t * l = value;
        char letter = key[0];
        if (!letter_has_miss_place(l)) {
            return;
        }
        if (!word_has(word, letter)) {
            c = 0;
        }
        for (int i = 0; i < strlen(word); i++) {
            if (!letter_is_miss_placed(l, i)) {
                continue;
            }
            if (word[i] == letter) {
                c = 0;
            }
        }
    }
    table_iterate(all_letters, iterator);
    return c;
}

int check_wrong_letters(table_t * all_letters, char * word) {
    int c = 1;
    void iterator(char * key, void * value) {
        letter_t * l = value;
        char letter = key[0];
        if (!letter_has_wrong(l)) {
            return;
        }
        if (word_count(word, letter) > letter_get_count(l)) {
            c = 0;
        }
    }
    table_iterate(all_letters, iterator);
    return c;
}