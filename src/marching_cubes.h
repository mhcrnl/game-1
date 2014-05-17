#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef VERTEX_ARRAY_H
#include "vertex_array.h"
#endif

#ifndef DENSITY_FIELD_H
#include "density_field.h"
#endif

struct cube_t {
  double          d[8];
  struct vector_t p[8];
};

void update_cube(
  struct vertex_array_t *va, 
  struct density_field_t *d, 
  struct vector_t *p, 
  double dx
);

#endif
