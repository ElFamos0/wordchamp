
#ifndef __dico__H__
#define __dico__H__

#include <stdbool.h>
#include "table.h"

table_t* dico_load(char* filename);
table_t* dico_load_size(char * filename, int taille);

#endif /* __dico__H__ */
