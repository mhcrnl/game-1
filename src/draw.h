#ifndef DRAW_H
#define DRAW_H

#include "vertex_array.h"

void vertex_array_draw_tri(struct vertex_array_t *va);
void vertex_array_draw_lines(struct vertex_array_t *va);
void vertex_array_draw_tri_normals(struct vertex_array_t *va, double s);

#endif
