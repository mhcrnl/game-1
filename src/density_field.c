#include "density_field.h"

#include "new.h"
#include "array_list.h"

struct sphere_t {
  struct vector_t p;
  double radius;
};

struct spherical_density_field_t {
  struct density_field_t field;
  struct sphere_t sphere;
};

struct spherical_array_density_field_t {
  struct density_field_t field;
  struct array_list_t spheres;
};

double spherical_density(struct density_field_t *field, struct vector_t *p);
double spherical_array_density(struct density_field_t *field, struct vector_t *p);
void spherical_normal(struct density_field_t *field, struct vector_t *p, struct vector_t *n);
void sample_normal(struct density_field_t *field, struct vector_t *p, struct vector_t *n);
double sphere_density(struct sphere_t *sphere, struct vector_t *p);

struct density_field_t* spherical_array_density_field_new(int capacity) 
{
  struct spherical_array_density_field_t *result = NEW(struct spherical_array_density_field_t);
  result->field.density = spherical_array_density;
  result->field.normal = sample_normal;
  array_list_init(&result->spheres, sizeof(struct sphere_t), capacity);
  return &result->field;
}

void spherical_array_density_field_push(struct density_field_t *field, struct vector_t *p, double radius) 
{
  struct spherical_array_density_field_t *s = (struct spherical_array_density_field_t *)field;
  struct sphere_t *sphere = array_list_next(&s->spheres);
  vector_copy(&sphere->p, p);
  sphere->radius = radius;
}

double spherical_array_density(struct density_field_t *field, struct vector_t *p)
{
  struct spherical_array_density_field_t *s = (struct spherical_array_density_field_t *)field;
  uint32_t i;
  struct sphere_t *sph;
  double density = 0.0;

  for(i=0;i<s->spheres.tail;++i) {
    sph = array_list_get(&s->spheres, i);
    density += sphere_density(sph, p);
  }

  return density;
}

struct density_field_t* spherical_density_field_new(struct vector_t *p, double radius) {
  struct spherical_density_field_t *field = NEW(struct spherical_density_field_t);
  field->field.density = spherical_density;
  field->field.normal = spherical_normal;
  vector_copy(&field->sphere.p, p);
  field->sphere.radius = radius;
  return &field->field;
}

double sphere_density(struct sphere_t *sphere, struct vector_t *p) {
  struct vector_t d;
  double l;
  vector_minus(&d, p, 1.0, &sphere->p);
  l = vector_length_squared(&d);
  return (sphere->radius*sphere->radius / l) - 1.0;
}

double spherical_density(struct density_field_t *field, struct vector_t *p) {
  struct spherical_density_field_t *s = (struct spherical_density_field_t *)field;
  return sphere_density(&s->sphere, p);
}

void spherical_normal(struct density_field_t *field, struct vector_t *p, struct vector_t *n) {
  struct spherical_density_field_t *s = (struct spherical_density_field_t *)field;
  vector_minus(n, p, 1.0, &s->sphere.p);
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

