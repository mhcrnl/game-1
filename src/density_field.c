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

void spherical_normal(struct density_field_t *field, struct vector_t *p, struct vector_t *n) {
  struct spherical_density_field_t *s = (struct spherical_density_field_t *)field;
  vector_minus(n, p, 1.0, &s->p);
  vector_normalize(n, n);
}

double sample_diff(struct density_field_t *field, struct vector_t *p, struct vector_t *dp) {
  struct vector_t p0, p1;
  vector_minus(&p0, p, 1, dp);
  vector_plus(&p1, p, 1, dp);
  return field->density(field, &p1) - field->density(field, &p0);
}

void sample_normal(struct density_field_t *field, struct vector_t *p, struct vector_t *n) {
  double dx = sample_diff(field, p, &U0) / 2.0;
  double dy = sample_diff(field, p, &U1) / 2.0;
  double dz = sample_diff(field, p, &U2) / 2.0;
  vector_set(n, dx, dy, dz);
  vector_normalize(n, n);
}

struct density_field_t* spherical_density_field_new(struct vector_t *p, double radius) {
  struct spherical_density_field_t *field = NEW(struct spherical_density_field_t);
  field->field.density = spherical_density;
  field->field.normal = spherical_normal;
  vector_copy(&field->p, p);
  field->radius = radius;
  return &field->field;
}
