#include "cube.h"

void vector_face(
  struct vector_t *r, 
  struct vector_t *p, 
  struct vector_t *d, 
  double ux, 
  double uy, 
  double uz
) {
  r->v[0] = p->v[0]/d->v[3] + (d->v[0]/d->v[3] * ux);
  r->v[1] = p->v[1]/d->v[3] + (d->v[1]/d->v[3] * uy);
  r->v[2] = p->v[2]/d->v[3] + (d->v[2]/d->v[3] * uz);
  r->v[3] = 1.0;
}

void quad(
          struct vertex_array_t *va, 
          struct vector_t *p, 
          struct vector_t *n, 
          struct vector_t *u, 
          double s
          ) 
{
  struct vector_t r;
  struct vector_t *a, *b, *c, *n1, *n2, *n3;

  if ( va->tail + 6 >= va->len ) {
    return;
  }

  vector_cross(&r, n, u);
  
  a  = va->v + va->tail + 0;
  b  = va->v + va->tail + 1;
  c  = va->v + va->tail + 2;

  n1 = va->n + va->tail + 0;
  n2 = va->n + va->tail + 1;
  n3 = va->n + va->tail + 2;

  va->tail += 3;

  vector_plus(a, p, -s, u);
  vector_plus(a, a, -s, &r);

  vector_plus(b, p, s,  u);
  vector_plus(b, b, -s, &r);

  vector_plus(c, p,  s, u);
  vector_plus(c, c,  s, &r);

  vector_copy(n1, n);
  vector_copy(n2, n);
  vector_copy(n3, n);

  a  = va->v + va->tail + 0;
  b  = va->v + va->tail + 1;
  c  = va->v + va->tail + 2;

  n1 = va->n + va->tail + 0;
  n2 = va->n + va->tail + 1;
  n3 = va->n + va->tail + 2;

  va->tail += 3;

  vector_plus(a, p, s, u);
  vector_plus(a, a, s, &r);

  vector_plus(b, p, -s, u);
  vector_plus(b, b,  s, &r);

  vector_plus(c, p, -s, u);
  vector_plus(c, c, -s, &r);

  vector_copy(n1, n);
  vector_copy(n2, n);
  vector_copy(n3, n);
}

void cube(struct vertex_array_t *va, struct vector_t *p0, double s) {
  struct vector_t n, p, u;
  int    i, j, k;

  for(i=0; i<3; ++i) {
    for(j=0; j<2; ++j) {
      for(k = 0; k<3; ++k) {
        n.v[k] = (k == i) ? (j == 0 ? 1.0 : -1.0) : 0.0;
      }
      n.v[3] = 1.0;
      if (i == 1) {
        vector_set(&u, 1, 0, 0);
      } else {
        vector_set(&u, 0, 1, 0);
      }
      vector_plus(&p, p0, s, &n);
      quad(va, &p, &n, &u, s);
    }
  }
}

void cube_lines(struct vertex_array_t *va, struct vector_t *p, double s) {
  struct vector_t p0, p1;
  int    i, j, k;

  for(i=0; i<2; ++i) {
    for(j=0; j<2; ++j) {
      for(k=0; k<2; ++k) {
        vector_copy(&p0, &ZERO);
        vector_plus(&p0, &p0, ((i*2)-1)*s, &U0);
        vector_plus(&p0, &p0, ((i*2)-1)*s, &U1);
        vector_plus(&p0, &p0, ((i*2)-1)*s, &U2);
        if ( i == 0 ) {
          vector_plus(&p1, &p0, 2*s, &U0);
          vertex_array_add_line(va, &p0, &p1);
        }
        if ( j == 0 ) {
          vector_plus(&p1, &p0, 2*s, &U1);
          vertex_array_add_line(va, &p0, &p1);
        }
        if ( k == 0 ) {
          vector_plus(&p1, &p0, 2*s, &U2);
          vertex_array_add_line(va, &p0, &p1);
        }
      }
    }
  }
}
