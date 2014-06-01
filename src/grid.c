#ifndef GRID_H
#define GRID_H

#include "vector.h"
#include "vertex_array.h"

void render_grid_lines(
                       struct vertex_array_t *va, 
                       struct vector_t *p, 
                       double dp, 
                       int np,
                       int i,
                       int j,
                       struct vector_t *u0,
                       struct vector_t *u1,
                       struct vector_t *u2
                       ) 
{
  struct vector_t p0, p1;
  vector_plus(&p0, p,   dp * i, u0);
  vector_plus(&p0, &p0, dp * j, u1);
  vector_plus(&p0, &p0, dp * -np, u2);
  vector_plus(&p1, &p0, dp * ((2*np)-1), u2);
  vertex_array_add_line(va, &p0, &p1);
}

void render_grid(struct vertex_array_t *va, 
                 struct vector_t *p, 
                 double dp, 
                 int np
                 ) 
{
  int i, j;
  for(i=-np; i<np; ++i) {
    for(j=-np; j<np; ++j) {
      render_grid_lines(va, p, dp, np, i, j, &U0, &U1, &U2);
      render_grid_lines(va, p, dp, np, i, j, &U1, &U2, &U0);
      render_grid_lines(va, p, dp, np, i, j, &U2, &U0, &U1);
    }
  }
}

#endif
