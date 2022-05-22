#include "../../open_dict.h"
#include "../solv_3b1b.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char filename[] = "../../../dicoz.txt";
    int val[5] = {0,0,0,0,0} ;
    pattern_t * pattern = create_pattern( val, "EEEEX");
    int n;
    int * count;
    bool * arr;
    possible_pre(&count,&arr,pattern);

    char ** arr2;
    arr2 = (char**) opendict_size(filename, 5, &n);

    for (int i = 0; i<n;i++) {
        // if (possible(arr2[i],pattern,count,arr)) {printf("%s\n", arr2[i]);}
        
        free(arr2[i]);
    }

    char * word = "PUISSANTES";
    int ** val_arr;
    gen_val_array(&val_arr,strlen(word));
    pattern_t *** pattern_arr = generate_all_pattern(word,val_arr);

    for(int i = 0; i<(int)pow(3,strlen(word));i++){

        print_pattern((*pattern_arr)[i]);

    }

    destroy_val_array(&val_arr,strlen(word));

    destroy_pattern_arr(pattern_arr);

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

    free(count);
    free(arr2);
    free(arr);

    destroy_pattern(pattern);

}
