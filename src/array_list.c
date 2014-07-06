#include "array_list.h"

#include "new.h"
#include <assert.h>

void array_list_init(struct array_list_t *lst, uint32_t element_size, uint32_t len) {
  lst->data = malloc(element_size * len);
  lst->len = len;
  lst->tail = 0;
  lst->element_size = element_size;
  memset(lst->data, 0, element_size * len);
}

struct array_list_t *array_list_new(uint32_t element_size, uint32_t len) {
  struct array_list_t *lst = NEW(struct array_list_t);
  array_list_init(lst, element_size, len);
  return lst;
}

void *array_list_get(struct array_list_t *lst, uint32_t i) {
  assert(i < lst->tail);
  return lst->data + (i * lst->element_size);
}

void array_list_push(struct array_list_t *lst, void *element) {
  if ( lst->tail < lst->len ) {
    memcpy(lst->data + ((lst->tail+1)*lst->element_size), element, lst->element_size);
  } else {
    void *new_data = malloc(lst->element_size * lst->len * 2);
    memcpy(new_data, lst->data, lst->element_size * lst->len);
    memcpy(new_data + ((lst->tail+1)*lst->element_size), element, lst->element_size);
    free(lst->data);
    lst->len *= 2;
    lst->data = new_data;
  }
}

void* array_list_next(struct array_list_t *lst) {
  if ( lst->tail < lst->len ) {
    lst->tail += 1;
  } else {
    void *new_data = malloc(lst->element_size * lst->len * 2);
    memcpy(new_data, lst->data, lst->element_size * lst->len);
    free(lst->data);
    lst->len *= 2;
    lst->data = new_data;
    lst->tail += 1;
  } 
  return lst->data + ((lst->tail - 1)*lst->element_size);
}

void array_list_pop(struct array_list_t *lst, void *element) {
  if ( lst->tail > 0 ) {
    lst->tail -= 1;
  }
}

