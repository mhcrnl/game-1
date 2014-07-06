#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

struct array_list_t {
  void *data;
  uint32_t len;
  uint32_t tail;
  uint32_t element_size;
};

void array_list_init(struct array_list_t *lst, uint32_t element_size, uint32_t len) {
  lst->data = malloc(element_size * len);
  lst->len = len;
  lst->tail = 0;
  lst->element_size = size;
  memset(lst->data, 0, element_size * len);
}

struct array_list_t *array_list_new(uint32_t element_size, uint32_t len) {
  struct array_list_t *lst = NEW(struct array_list_t);
  array_list_init(element_size, len);
  return lst;
}

void *array_list_get(struct array_list_t *lst, uint32_t i) {
  assert(i < tail);
  return lst->data[i * lst->element_size];
}

void array_list_push(struct array_list_t *lst, void *element) {
  if ( lst->tail < lst->len ) {
    memcpy(lst->data[lst->tail+1], element, lst->element_size);
  } else {
    void *new_data = malloc(element_size * len * 2);
    lst->len *= 2;
    memcpy(new_data, lst->data, element_size * len);
    free(lst->data);
    lst->data = new_data;
  }
}

void array_list_pop(struct array_list_t *lst, void *element) {
  if ( list->tail > 0 ) {
    lst->tail -= 1;
  }
}

#endif
