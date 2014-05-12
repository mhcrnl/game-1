#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

struct vertex_array_t {
  int len;
  int tail;
  struct vector_t *v;
  struct vector_t *n;
};

#endif
