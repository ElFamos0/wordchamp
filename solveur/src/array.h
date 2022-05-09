#ifndef array_h
#define array_h
#define DEFAULT_SIZE 1

typedef struct array_t {
    size_t size;
    size_t capacity;
    size_t element_size;
    char *data;
} array_t;

array_t * create_array(size_t element_size);
int add_element(array_t *array, size_t index, void *element);
int array_resize(array_t *array);
void * get_array_element(array_t *array, size_t index);
void free_array(array_t *array);

#endif 
