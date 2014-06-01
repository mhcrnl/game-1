#include "vector.h"

#include <math.h>
#include <string.h>

struct vector_t U0 = { { 1.0, 0.0, 0.0, 1.0 } };
struct vector_t U1 = { { 0.0, 1.0, 0.0, 1.0 } };
struct vector_t U2 = { { 0.0, 0.0, 1.0, 1.0 } };
struct vector_t ZERO = { { 0.0, 0.0, 0.0, 1.0 } };
struct vector_t ONES = { { 1.0, 1.0, 1.0, 1.0 } };

void vector_cross(struct vector_t *r, struct vector_t *a, struct vector_t *b) {
  r->v[0] = (a->v[1] * b->v[2]) - (a->v[2] * b->v[1]);
  r->v[1] = (a->v[0] * b->v[2]) - (a->v[2] * b->v[0]);
  r->v[2] = (a->v[0] * b->v[1]) - (a->v[1] * b->v[0]);
  r->v[3] = a->v[3] * b->v[3];
}

double vector_length_squared(struct vector_t *a) {
  return (a->v[0] * a->v[0] + a->v[1] * a->v[1] + a->v[2] * a->v[2]) 
    / (a->v[3] * a->v[3]);
}

double vector_length(struct vector_t *a) {
  return sqrt(vector_length_squared(a));
}

void vector_normalize(struct vector_t *r, struct vector_t *a) {
  double l = vector_length_squared(a);
  r->v[0] = a->v[0];
  r->v[1] = a->v[1];
  r->v[2] = a->v[2];
  r->v[3] = sqrt(l);
}  

double vector_dot(struct vector_t *a, struct vector_t *b) {
  double r = 0;
  int i;
  for(i=0;i<3;++i) {
    r += a->v[i] * b->v[i];
  }
  r /= a->v[3] * b->v[3];
  return r;
}

void vector_minus(struct vector_t *r, struct vector_t *a, double alpha, struct vector_t *b) {
  int i;
  for(i=0;i<3;++i) {
    r->v[i] = a->v[i] / a->v[3] - (alpha * (b->v[i] / b->v[3]));
  }
  r->v[3] = 1.0;
}

void vector_set(struct vector_t *r, double x, double y, double z) {
  r->v[0] = x;
  r->v[1] = y;
  r->v[2] = z;
  r->v[3] = 1.0;
}

void vector_plus(struct vector_t *r, struct vector_t *a, double alpha, struct vector_t *b) {
  int i;
  for(i=0;i<3;++i) {
    r->v[i] = a->v[i] / a->v[3] + (alpha * (b->v[i] / b->v[3]));
  }
  r->v[3] = 1.0;
}

void vector_times(struct vector_t *r, struct vector_t *a, double b) {
  int i;
  for(i=0;i<3;++i) {
    r->v[i] = a->v[i];
  }
  r->v[3] = a->v[3] / b;
}

void vector_copy(struct vector_t *r, struct vector_t *a) {
  memcpy(r, a, sizeof(struct vector_t));
}

void fvector_set(struct fvector_t *r, float x, float y, float z) {
  r->v[0] = x;
  r->v[1] = y;
  r->v[2] = z;
  r->v[3] = 1;
}

void fvector_copy_vector(struct fvector_t *r, struct vector_t *a) {
  int i;
  for(i=0;i<4;++i) {
    r->v[i] = a->v[i];
  }
}
