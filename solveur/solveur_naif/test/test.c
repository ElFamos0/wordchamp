#define SNOW_ENABLED

#include "../src/wordlist.h"

#include "snow.h"
#define assert_false(expr) assert(! expr)

describe(test_one) {
    it("Remove test") {
        wordlist_t * wl = wordlist_create();

        wordlist_add(wl, "REBUS");
        wordlist_add(wl, "REBUS");
        wordlist_add(wl, "MACON");
        wordlist_add(wl, "DUREE");
        wordlist_add(wl, "TEMPS");
        wordlist_add(wl, "VOILE");
        wordlist_add(wl, "RUINE");
        wordlist_add(wl, "ORTIE");
        wordlist_add(wl, "PRIER");
        wordlist_add(wl, "GAUSS");
        wordlist_add(wl, "TAXER");
        wordlist_add(wl, "SALAD");

        wordlist_remove_words(wl, "PARRE", "00102");
        printf("\n");
        for (int i = 0; i < wl->size; i++) {
            printf("%s\n", wl->words[i]->word);
        }
        printf("\n");

        wordlist_destroy(wl);
    }

    it("Random test") {
        wordlist_t * wl = wordlist_create();

        wordlist_add(wl, "REBUS");
        wordlist_add(wl, "REBUS");
        wordlist_add(wl, "MACON");
        wordlist_add(wl, "DUREE");
        wordlist_add(wl, "TEMPS");
        wordlist_add(wl, "VOILE");
        wordlist_add(wl, "RUINE");
        wordlist_add(wl, "ORTIE");
        wordlist_add(wl, "PRIER");
        wordlist_add(wl, "GAUSS");
        wordlist_add(wl, "TAXER");
        wordlist_add(wl, "SALAD");

        printf("\n");
        word_t * w = wordlist_pick_random_word(wl);
        printf("%s\n", w->word);
        printf("\n");

        wordlist_destroy(wl);
    }

    it("Open file test") {
        wordlist_t * wl = wordlist_create();

        wordlist_open_file(wl, "dict.txt", 5);
        // printf("\n");
        // for (int i = 0; i < wl->size; i++) {
        //     printf("%s\n", wl->words[i]->word);
        // }
        // printf("\n");

        wordlist_destroy(wl);
    }
}

snow_main();
