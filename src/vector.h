#ifndef VECTOR_H
#define VECTOR_H

struct vector_t {
  double v[4];
};

struct fvector_t {
  float v[4];
};

extern struct vector_t U0;
extern struct vector_t U1;
extern struct vector_t U2;
extern struct vector_t ZERO;
extern struct vector_t ONES;

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
void fvector_set(struct fvector_t *r, float x, float y, float z);

static inline double vx(struct vector_t *v) {
  return v->v[0] / v->v[3];
}

static inline double vy(struct vector_t *v) {
  return v->v[1] / v->v[3];
}

static inline double vz(struct vector_t *v) {
  return v->v[2] / v->v[3];
}

#endif
