#ifndef linked_list_h
#define linked_list_h

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

typedef struct linked_list_t linked_list_t;
struct linked_list_t {
    struct linked_list_t_element* next;
};

typedef struct linked_list_t_element linked_list_t_element;
struct linked_list_t_element {
    char* value;
    struct linked_list_t_element* next;
};

linked_list_t* list_create();
bool list_is_empty(linked_list_t*);
void list_prepend(linked_list_t*, char*);
char* list_first(linked_list_t*);
void list_append(linked_list_t*, char*);
char* list_last(linked_list_t*);
void list_print(linked_list_t*);
void list_destroy(linked_list_t*);
void list_insert(linked_list_t*, char*, unsigned int);
char* list_get(linked_list_t*, unsigned int);
unsigned int list_index_of(linked_list_t*, char*);

#endif