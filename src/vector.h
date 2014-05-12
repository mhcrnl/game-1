#ifndef VECTOR_H
#define VECTOR_H

struct vector_t {
  double v[4];
};

struct fvector_t {
  float v[4];
};

void vector_cross(struct vector_t *r, struct vector_t *a, struct vector_t *b);
double vector_length_squared(struct vector_t *a);
void vector_normalize(struct vector_t *r, struct vector_t *a);
double vector_dot(struct vector_t *a, struct vector_t *b);
void vector_minus(struct vector_t *r, struct vector_t *a, double alpha, struct vector_t *b);
void vector_set(struct vector_t *r, double x, double y, double z);
void vector_plus(struct vector_t *r, struct vector_t *a, double alpha, struct vector_t *b);
void vector_times(struct vector_t *r, struct vector_t *a, double b);
void vector_copy(struct vector_t *r, struct vector_t *a);
void fvector_copy_vector(struct fvector_t *r, struct vector_t *a);

#endif
