#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "naif.h"
#include "open_dict.h"
#include "linked_list.h"

linked_list_t* generateList() {
    linked_list_t* liste = list_create();
    int n;
    char ** dico = opendict("../build/dico.txt", &n);
    for (int i = 0; i < n; i++) {
        list_append(liste, dico[i]);
    }
    // for (int i = 0; i < n; i++) {
    //     free(dico[i]);
    // }
    free(dico);
    return liste;
}

void extractList(linked_list_t* liste, int na, char** absentes, int nj, strInt_t* jaunes, int nv, strInt_t* vertes) {
    linked_list_t_element* curr_elmt = liste->next;
    bool keep = true;
    bool first = true;

    // on travaille sur l'element suivant pour pouvoir raccrocher le debut de la liste au bon endroit
    linked_list_t_element* next_elmt = curr_elmt;

    while ((next_elmt != NULL)) {
        // printf("mot :::: %s\n", next_elmt->value);
        // list_print(liste);
        keep = true;
        //  on applique le premier filtre : on parcourt les lettres vertes, et on verifie qu'elles
        // sont a la bonne place dans le mot, si elles n'y sont pas, on prevoit de supprimer 
        // le mot de la liste
        for (int i = 0; i<nv; i++) {
            if (keep && (next_elmt->value[vertes[i].position]!=vertes[i].lettre[0])) {
                keep = false;
            }
        }

        // on parcourt ensuite les lettres absentes
        for (int i = 0; i<na; i++) {
            // printf("mot : %s, lettre : %s, res : %s", next_elmt->value, absentes[i], strstr(next_elmt->value, absentes[i]));
            if (keep && (strstr(next_elmt->value, absentes[i]))!= NULL) {
                keep = false;
            }
        }

        // on parcourt enfin les lettres jaunes
        for (int i = 0; i<nj; i++) {
            if (keep && (strstr(next_elmt->value, jaunes[i].lettre))== NULL) {
                keep = false;
            } else if (keep && (next_elmt->value[jaunes[i].position]==jaunes[i].lettre[0])) {
                keep = false;
            }
        }

        // on prepare l'element suivant et on supprime l'actuel qui ne respecte pas les conditions
        // on libere bien la str et l'element
        if (!keep) {
            if (first) {
                linked_list_t_element* temp = next_elmt;
                next_elmt = next_elmt->next;
                liste->next = next_elmt;
                free(temp->value);
                free(temp);
            } else {
                linked_list_t_element* temp = next_elmt;
                next_elmt = next_elmt->next;
                curr_elmt->next = next_elmt;
                free(temp->value);
                free(temp);
            }
        } else {
            if (first) {
                liste->next = next_elmt;
                curr_elmt = next_elmt;
                next_elmt = next_elmt->next;
                first = false;
            } else {
                curr_elmt->next = next_elmt;
                curr_elmt= next_elmt;
                next_elmt= next_elmt->next;
            }
        }
    }
}