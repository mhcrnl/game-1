#include "vertex_array.h"

#ifndef NEW_H
#include "new.h"
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

struct vertex_array_t *vertex_array_new(int len) {
  struct vertex_array_t *vertex_array = NEW(struct vertex_array_t);
  vertex_array->len  = len;
  vertex_array->tail = 0;
  vertex_array->v = NEW_ARRAY(struct vector_t, len);
  vertex_array->n = NEW_ARRAY(struct vector_t, len);
  return vertex_array;
}

