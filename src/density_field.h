#ifndef DENSITY_FIELD_H
#define DENSITY_FIELD_H

#ifndef VECTOR_H
#include "vector.h"
#endif

struct density_field_t;
struct spherical_array_density_field_t;

typedef double (*density_function_t)(struct density_field_t *field, struct vector_t *p);

typedef void (*normal_function_t)(struct density_field_t *field, struct vector_t *p, struct vector_t *n);

struct density_field_t {
  density_function_t density;
  normal_function_t normal;
};

struct density_field_t* spherical_array_density_field_new(int capacity);
void spherical_array_density_field_push(struct density_field_t *field, struct vector_t *p, double radius);

#endif
