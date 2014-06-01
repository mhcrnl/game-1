#include "density_field.h"

#ifndef NEW_H
#include "new.h"
#endif

struct spherical_density_field_t {
  struct density_field_t field;
  struct vector_t p;
  double radius;
};

double spherical_density(struct density_field_t *field, struct vector_t *p) {
  struct spherical_density_field_t *s = (struct spherical_density_field_t *)field;
  struct vector_t d;
  double l;
  vector_minus(&d, p, 1.0, &s->p);
  l = vector_length_squared(&d);
  return (s->radius*s->radius / l) - 1.0;
}

struct density_field_t* spherical_density_field_new(struct vector_t *p, double radius) {
  struct spherical_density_field_t *field = NEW(struct spherical_density_field_t);
  field->field.density = spherical_density;
  vector_copy(&field->p, p);
  field->radius = radius;
  return &field->field;
}
