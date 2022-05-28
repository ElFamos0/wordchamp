#include "table.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int hash(char *some_value) {
    int res = 0;
    int i = 0;

    for (i = 0; some_value[i] != '\0'; i++) {
        res = res + some_value[i];
    }
    return res;
}

table_t *table_create(int size) {
    table_t *table = calloc(1, sizeof(table_t));

    assert(table != NULL);

    table->list = calloc(size, sizeof(list_t *));
    table->size = size;

    for (int i = 0; i < size; i++) {
        list_t * list = list_create();
        table->list[i] = list;
    }

    return table;
}

void table_destroy(table_t *table) {
    assert(table != NULL);
    for (int i = 0; i < table->size; i++) {
        list_destroy(table->list[i]);
    }
    free(table->list);
    free(table);
}

int table_indexof(table_t *table, char *key) {
    assert(table != NULL);

    int index = hash(key) % table->size;
    return index;
}

bool table_add(table_t *table, char *key, void * value) {
    assert(table != NULL);
    assert(key != NULL);

    int index = table_indexof(table, key);
    list_t *list = table->list[index];
    if (list_contains(list, key)) {
        return false;
    }
    list_append(list, key, value);

    return true;
}

bool table_contains(table_t *table, char *key) {
    assert(table != NULL);
    assert(key != NULL);

    int index = table_indexof(table, key);
    list_t *list = table->list[index];
    return list_contains(list, key);
}

void * table_get(table_t *table, char *key) {
    assert(table != NULL);
    assert(key != NULL);
    
    int index = table_indexof(table, key);
    list_t *list = table->list[index];
    return list_find(list, key);
}

void table_iterate(table_t *table, void (*function)(char *, void *)) {
    assert(table != NULL);
    assert(function != NULL);

    for (int i = 0; i < table->size; i++) {
        list_t *list = table->list[i];
        list_iterate(list, function);
    }
}