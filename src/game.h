#ifndef GAME_H
#define GAME_H

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef DENSITY_FIELD_H
#include "density_field.h"
#endif

struct state_t {
  struct vertex_array_t *box;
  struct vector_t      pos;
  struct vector_t      fow;
  struct vector_t      left;
  int                  mx;
  int                  mz;
  struct timespec      last_update;
  double a1, a2;
  int    px, py;
  int    button_down;
  int    quit;

  struct vertex_array_t *va;
  struct density_field_t *field;
};


struct vertex_array_t *vertex_array_new(int len);
void vector_minus(struct vector_t *r, struct vector_t *a, double alpha, struct vector_t *b);
void vector_plus(struct vector_t *r, struct vector_t *a, double alpha, struct vector_t *b);
void vector_copy(struct vector_t *r, struct vector_t *a);
void print_vector(char *name, struct vector_t *v);
void fvector_copy_vector(struct fvector_t *r, struct vector_t *a);

#endif
