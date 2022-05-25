#include "game.h"

int word_size_file() {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen("wsolf.txt", "r");
    // La taille du mot est sur la premiere ligne (normalement :v)
    read = getline(&line, &len, fp);
    int count = atoi(line);
    fclose(fp);

    // magie ?
    free(line);

    return count;
}

void start_game(int word_size, bool interactive) {
    wordlist_t * wl = wordlist_create();
    wordlist_open_file(wl, "dict.txt", word_size);
    if (interactive) {
        printf("Bienvenue sur le solveur naïf!\n");
        printf("Le dictionnaire contient %d mots de %d lettres.\n", wl->size, word_size);
        printf("Voici la première suggestion : ");
    }

    // Le premier mot
    word_t * guess = wordlist_pick_random_word(wl);
    printf("%s\n", guess->word);
    while (1) {

        // On récupére le résultat depuis la stdout

        if (interactive) {
            printf("Votre proposition : ");
        }
        char result[word_size+1];
        fgets(result, word_size+1, stdin);

        if (strcmp(result, "-1") == 0) {
            if (interactive) {
                printf("Fin de partie\n");
            }
            break;
        }

        if (strlen(result) != word_size) {
            if (interactive) {
                printf("Résultat de taille invalide\n");
            }
            continue;
        }
        
        if (!word_has(result, '0') && !word_has(result, '1')) {
            if (interactive) {
                printf("Réponse trouvée\n");
            }
            break;
        }

        // On analyse le résultat
        wordlist_remove_words(wl, guess->word, result);

        guess = wordlist_pick_random_word(wl);
        if (interactive) {
            printf("Voici la prochaine proposition : ");
        }
        printf("%s\n", guess->word);
    }

    wordlist_destroy(wl);
}

int main(int argc, char * argv[]) {
    // Taille du mot en argument si besoin (ou pour le testeur)
    int word_size;
    if (argc > 1) {
        word_size = atoi(argv[1]);
    } else {
        word_size = word_size_file();
    }

    // Deuxieme argument pour le mode de fonctionnement
    bool interactive = false;
    if (argc > 2) {
        interactive = true;
    }
    
    start_game(word_size, interactive);
    
    return 0;
}