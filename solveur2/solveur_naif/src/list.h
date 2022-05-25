
#ifndef __LIST_H__
#define __LIST_H__
#define DEFAULT_CAPACITY 1

#include <stdbool.h>
#include <stddef.h>

struct _element_t
{
    char * key;
    void * value;
};

typedef struct _element_t element_t;

struct _list_t
{
    int size;
    int capacity;
    element_t ** data;
};

typedef struct _list_t list_t;

list_t *list_create();

void list_destroy(list_t *one_list);

bool list_is_empty(list_t *one_list);

int list_resize(list_t *one_list);

void list_add(list_t *list, size_t index, char *key, void * value);

void list_append(list_t *one_list, char *one_key, void * one_value);

void * list_get(list_t *one_list, size_t index);

void element_print(element_t *one_element);

void list_print(list_t *one_list);

bool list_contains(list_t *one_list, char *one_key);

void * list_find(list_t *one_list, char *one_key);

void list_iterate(list_t *one_list, void (*one_function)(char *, void *));

#endif /* __LIST_H__ */
