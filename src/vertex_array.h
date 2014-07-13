#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

struct vertex_array_t {
  int len;
  int tail;
  struct texture_t *tex;
  struct vector_t  *v;
  struct vector_t  *n;
  struct vector_t  *st;
};

struct vertex_array_t *vertex_array_new(int len);
void vertex_array_add_line(
                           struct vertex_array_t *va, 
                           struct vector_t *p0, 
                           struct vector_t *p1
                           );

#endif
