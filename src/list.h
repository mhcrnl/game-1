#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "std.h"

struct list_t {
  uint8_t  *data;
  uint32_t len;
  uint32_t tail;
  uint32_t element_size;
};

void list_init(struct list_t *lst, uint32_t element_size, uint32_t len);
struct list_t *list_new(uint32_t element_size, uint32_t len);
void *list_get(struct list_t *lst, uint32_t i);
void list_push(struct list_t *lst, void *element);
void list_pop(struct list_t *lst, void *element);



#endif
