#ifndef DENSITY_FUNCTION_H
#define DENSITY_FUNCTION_H

struct density_field_t;

typedef double (*density_function_t)(struct density_field_t *field, struct vector_t *p);

struct density_field_t {
  density_function_t *density;
};

#endif
