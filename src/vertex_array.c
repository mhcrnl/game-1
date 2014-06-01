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

void vertex_array_add_line(struct vertex_array_t *va, 
                                             struct vector_t *p0, 
                                             struct vector_t *p1)
{
  if ( va->tail+2 < va->len ) {
    vector_copy(&va->v[va->tail], p0);
    vector_copy(&va->v[va->tail+1], p1);
    vector_copy(&va->n[va->tail], p0);
    vector_copy(&va->n[va->tail+1], p1);
    va->tail += 2;
  }
}
