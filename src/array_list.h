#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdint.h>
#include <string.h>

struct array_list_t {
  char *data;
  uint32_t len;
  uint32_t tail;
  uint32_t element_size;
};

void array_list_init(struct array_list_t *lst, uint32_t element_size, uint32_t len);
struct array_list_t *array_list_new(uint32_t element_size, uint32_t len);
void *array_list_get(struct array_list_t *lst, uint32_t i);
void array_list_push(struct array_list_t *lst, void *element);
void* array_list_next(struct array_list_t *lst);
void array_list_pop(struct array_list_t *lst, void *element);

#endif
