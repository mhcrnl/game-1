#include "draw.h"
#include "gl.h"
#include "vector.h"

void gl_vertex(struct vector_t *v) {
  glVertex4d(v->v[0], v->v[1], v->v[2], v->v[3]);
}

void gl_normal(struct vector_t *v) {
  glNormal3d(v->v[0]/v->v[3], v->v[1]/v->v[3], v->v[2]/v->v[3]);
}

void gl_tex_coord(struct vector_t *v) {
  glTexCoord2d(v->v[0]/v->v[3], v->v[1]/v->v[3]);
}

void vertex_array_draw_tri(struct vertex_array_t *va) {
  int i;
  if ( va->tex != 0 ) {
    
  }
  glBegin(GL_TRIANGLES);
  for(i=0; i<va->tail; i++) {
    gl_normal(va->n + i);
    gl_vertex(va->v + i);
    if ( va->tex != 0 ) {
      gl_tex_coord(va->st + i);
    }
  }
  glEnd();
}

void vertex_array_draw_lines(struct vertex_array_t *va) {
  int i;
  glBegin(GL_LINES);
  for(i=0; i<va->tail; i++) {
    gl_normal(va->n + i);
    gl_vertex(va->v + i);
  }
  glEnd();
}

void vertex_array_draw_tri_normals(struct vertex_array_t *va, double s) {
  struct vector_t v2;
  int i;

  glLineWidth(2);
  glBegin(GL_LINES);
  for(i=0; i<va->tail; ++i) {
    vector_plus(&v2, va->v + i, s, va->n + i);
    gl_vertex(va->v + i);
    gl_vertex(&v2);
  }
  glEnd();
}


  


