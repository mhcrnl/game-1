#ifndef CUBE_H
#define CUBE_H

#ifndef VECTOR_ARRAY_H
#include "vertex_array.h"
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

void vector_face(
                 struct vector_t *r, 
                 struct vector_t *p, 
                 struct vector_t *d, 
                 double ux, 
                 double uy, 
                 double uz
                 );

void quad(
          struct vertex_array_t *va, 
          struct vector_t *p, 
          struct vector_t *n, 
          struct vector_t *u, 
          double s);

void cube(struct vertex_array_t *va, struct vector_t *p0, double s);
void cube_lines(struct vertex_array_t *va, struct vector_t *p0, double s);

#endif
