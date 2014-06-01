#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#include "vector.h"
#include "vertex_array.h"
#include "density_field.h"

struct cube_t {
  double          d[8];
  struct vector_t p[8];
};

void update_cube(
  struct vertex_array_t *va, 
  struct vertex_array_t *val,
  struct density_field_t *d, 
  struct vector_t *p, 
  double dx
);

void render_field(
  struct vertex_array_t *va, 
  struct vertex_array_t *val,
  struct density_field_t *f, 
  struct vector_t *c,
  double d,
  int n
);


#endif
