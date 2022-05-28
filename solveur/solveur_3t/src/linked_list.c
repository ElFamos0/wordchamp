#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "linked_list.h"

linked_list_t* list_create() {
    linked_list_t* list = malloc(sizeof(linked_list_t));
    list->next = NULL;
    return list;
}

bool list_is_empty(linked_list_t* one_list) {
    return one_list->next==NULL;
}

void list_prepend(linked_list_t* one_list, char* one_value) {
    linked_list_t_element* premier = malloc(sizeof(linked_list_t_element));
    premier->next = one_list->next;
    premier->value = one_value; 
    one_list->next=premier;
}

char* list_first(linked_list_t* one_list) {
    return one_list->next->value;
}

void list_append(linked_list_t* one_list, char* one_value) {
    linked_list_t_element* new_element = malloc(sizeof(linked_list_t_element));
    new_element->value = one_value;
    new_element->next = NULL;
    if (list_is_empty(one_list)) {
        one_list->next = new_element;
    } else {
        linked_list_t_element* last = one_list->next;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next=new_element;
    }
}

char* list_last(linked_list_t* one_list) {
    if (list_is_empty(one_list)) {
        return "La liste est vide : pas de dernier élément !";
    } else {
        linked_list_t_element* curr = one_list->next;
        while (curr->next!=NULL) {
            curr = curr->next;
        }
        return curr->value;
    }
}

void list_print(linked_list_t* one_list) {
    if (list_is_empty(one_list)) {
        printf("La liste est vide");
    } else {
        linked_list_t_element* curr = one_list->next;
        while (curr != NULL) {
            printf("[%s]", curr->value);
            curr = curr->next;
        }
    }
    printf("\n");
}

void list_destroy(linked_list_t* one_list) {
    linked_list_t_element* curr = one_list->next;
    free(one_list);
    while (curr!=NULL) {
        linked_list_t_element* next = curr->next;
        free(curr);
        curr = next;
    }
}

void list_insert(linked_list_t* one_list, char* one_value, unsigned int one_pos) {
    unsigned int curr_pos = 0;
    linked_list_t_element* new_element = malloc(sizeof(linked_list_t_element));
    new_element->value = one_value;
    new_element->next = NULL;
    linked_list_t_element* curr = one_list->next;
    while (curr_pos != one_pos-1) {
        curr = curr->next;
        curr_pos++;
    }
    new_element->next = curr->next;
    curr->next = new_element;
}

char* list_get(linked_list_t* one_list, unsigned int one_pos) {    
    unsigned int curr_pos = 0;
    linked_list_t_element* curr = one_list->next;
    while (curr_pos != one_pos) {
        curr = curr->next;
        curr_pos++;
    }
    return curr->value;
}

unsigned int list_index_of(linked_list_t* one_list, char* one_value) {
    unsigned int curr_pos = 0;
    linked_list_t_element* curr = one_list->next;
    while (curr != NULL) {
        if (curr->value == one_value) {
            return curr_pos;
        }
        curr = curr->next;
        curr_pos++;
    }
    return -1;
}
