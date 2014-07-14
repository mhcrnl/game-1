#include "list.h"
#include "new.h"
#include <string.h>
#include <assert.h>

void list_init(struct list_t *lst, uint32_t element_size, uint32_t len) {
  lst->data = NEW_ARRAY(uint8_t, element_size * len);
  lst->len = len;
  lst->tail = 0;
  lst->element_size = element_size;
  memset(lst->data, 0, element_size * len);
}

struct list_t *list_new(uint32_t element_size, uint32_t len) {
  struct list_t *lst = NEW(struct list_t);
  list_init(lst, element_size, len);
  return lst;
}

void *list_get(struct list_t *lst, uint32_t i) {
  assert(i < lst->tail);
  return lst->data + (i * lst->element_size);
}

void list_push(struct list_t *lst, void *element) {
  if ( lst->tail < lst->len ) {
    memcpy(lst->data + lst->tail + 1, element, lst->element_size);
  } else {
    void *new_data = NEW_ARRAY(uint8_t, lst->element_size * lst->len * 2);
    lst->len *= 2;
    memcpy(new_data, lst->data, lst->element_size * lst->len);
    free(lst->data);
    lst->data = new_data;
  }
}

void list_pop(struct list_t *lst, void *element) {
  if ( lst->tail > 0 ) {
    lst->tail -= 1;
  }
}
