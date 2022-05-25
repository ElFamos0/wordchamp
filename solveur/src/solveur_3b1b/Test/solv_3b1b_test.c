#include "../solv_3b1b.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char filename[] = "../../../dicoz.txt";
    // int val[5] = {1,0,2,0,0} ;
    // pattern_t * pattern = create_pattern( val, "MAISO");
    // int n;
    // int * count;
    // bool * arr;
    // possible_pre(&count,&arr,pattern);

    table_t * table = dico_load_size(filename,7);
    best_guess_v2(table,table,7);


                     // Test de generate_all_pattern

    // char * word = "SASSE";
    // int ** val_arr;
    // gen_val_array(&val_arr,strlen(word));
    // pattern_t *** pattern_arr = generate_all_pattern(word,val_arr);

    // for(int i = 0; i<(int)pow(3,strlen(word));i++){

    //     print_pattern((*pattern_arr)[i]);

    // }

    // destroy_val_array(&val_arr,strlen(word));

    // destroy_pattern_arr(pattern_arr);


                        // Test de gen_val_array

    // int size = 5;

    // int ** val_arr;
    // gen_val_array(&val_arr, size);

    // for(int i = 0; i<(int)pow(3,size); i++ ) {

    //     printf("{%d",val_arr[i][0]);
    //     for(int j = 1; j< size;j++){

    //         printf(",%d",val_arr[i][j]);
    //     }
    //     printf("}\n");
        
    // }

    // destroy_val_array(&val_arr,size);



    // if (possible(arr2[i],pattern,count,arr)) {printf("%s\n", arr2[i]);}


    // printf("%d",possible("PLAID",pattern,count,arr));
    // printf("%f\n",calculate_proba(pattern,table));


    //            Lecture de tous les mots



    // update_possible_words(table,pattern);

    // table_t * table_dico = dico_load_size(filename,5);

    // for(int indice = 0; indice < table->size; indice ++) {

    //     list_t * liste = table->tab[indice];
    //     int size;
    //     char *** arr_list = list_to_arr(liste,&size);


    //     for(int i =0; i< size; i++) {

    //         printf("%s\n", (*arr_list)[i]);


    //     }

    //     destroy_list_arr(arr_list,size);

    //  }


    // destroy_pattern(pattern);

    // char * word = "SASSE";
    // int ** val_arr;
    // gen_val_array(&val_arr,strlen(word));
    // pattern_t *** pattern_arr = generate_all_pattern(word,val_arr);
    // int size_dico;
    // char *** all_words_dico = all_words(table,&size_dico);

    // for(int i = 0; i<(int)pow(3,strlen(word));i++){

    //     double p = calculate_proba((*pattern_arr)[i],table,all_words_dico,size_dico);
    //     if (p> 0) {
    //     printf("%f,",p);
    //     print_pattern((*pattern_arr)[i]);
    //     }

    // }
    
    // destroy_all_words(all_words_dico,size_dico);




    // destroy_val_array(&val_arr,strlen(word));

    // destroy_pattern_arr(pattern_arr);


    table_destroy(table);
    // table_destroy(table_dico);

    // free(count);
    // free(arr);


}
