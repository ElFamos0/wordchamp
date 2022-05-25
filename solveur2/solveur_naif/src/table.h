#ifndef __TABLE__H__
#define __TABLE_H__

#include <stdbool.h>
#include "list.h"

typedef struct _table_t {
    list_t ** list;
    size_t size;
} table_t;

int hash(char *some_value);

table_t *table_create(int size);

void table_destroy(table_t *one_table);

int table_indexof(table_t *one_table, char *one_key);

bool table_add(table_t *one_table, char *one_key, void * one_value);

bool table_contains(table_t *one_table, char *one_key);

void * table_get(table_t *one_table, char *one_key);

void table_iterate(table_t *one_table, void (*one_function)(char *, void *));

#endif /* __TABLE_H__ */
