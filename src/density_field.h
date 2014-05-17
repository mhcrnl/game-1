#ifndef DENSITY_FIELD_H
#define DENSITY_FIELD_H

#ifndef VECTOR_H
#include "vector.h"
#endif

struct density_field_t;

typedef double (*density_function_t)(struct density_field_t *field, struct vector_t *p);

struct density_field_t {
  density_function_t density;
};

struct density_field_t* spherical_density_field_new(struct vector_t *p, double radius);

#endif
