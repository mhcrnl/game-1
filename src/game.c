#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifndef GAME_H
#include "game.h"
#endif

#ifndef VERTEX_ARRAY_H
#include "vertex_array.h"
#endif

#ifndef NEW_H
#include "new.h"
#endif

#ifndef MARCHING_CUBES_H
#include "marching_cubes.h"
#endif

void glutLeaveMainLoop();

float COLOR_RED[]      = {1.0, 0.0, 0.0, 1.0};  
float COLOR_YELLOW[]   = {1.0, 1.0, 0.0, 1.0};  
float COLOR_WHITE[]    = {1.0, 1.0, 1.0, 1.0};  
float COLOR_GRAY2[]     = {0.2, 0.2, 0.2, 1.0};  
float COLOR_GRAY9[]     = {0.9, 0.9, 0.9, 1.0};  

struct vector_t U0 = { { 1.0, 0.0, 0.0, 1.0 } };
struct vector_t U1 = { { 0.0, 1.0, 0.0, 1.0 } };
struct vector_t U2 = { { 0.0, 0.0, 1.0, 1.0 } };
struct vector_t ZERO = { { 0.0, 0.0, 0.0, 1.0 } };
struct vector_t ONES = { { 1.0, 1.0, 1.0, 1.0 } };

// i (u2 v3 - u3 v2)
// j (u1 v3 - u3 v1)
// k (u1 v2 - u2 v1)

// i (u1 v2 - u2 v1)
// j (u0 v2 - u2 v0)
// k (u0 v1 - u1 v0)



void face_normal(struct vector_t *v, struct vector_t *n) {
  struct vector_t s, t;
  vector_minus(&s, &v[0], 1.0, &v[1]); 
  vector_minus(&t, &v[2], 1.0, &v[1]);
  vector_cross(n, &s, &t);
  vector_normalize(n, n);

  vector_copy(&n[1], &n[0]);
  vector_copy(&n[2], &n[0]);
}

void vertex_array_normals(struct vertex_array_t *f) {
  int i;
  for(i=0;i<f->tail;i+=3) {
    face_normal(f->v + i, f->n + i);
  }
}

void vector_face(
  struct vector_t *r, struct vector_t *p, struct vector_t *d, 
  double ux, double uy, double uz
) {
  r->v[0] = p->v[0]/d->v[3] + (d->v[0]/d->v[3] * ux);
  r->v[1] = p->v[1]/d->v[3] + (d->v[1]/d->v[3] * uy);
  r->v[2] = p->v[2]/d->v[3] + (d->v[2]/d->v[3] * uz);
  r->v[3] = 1.0;
}

void quad(struct vertex_array_t *va, struct vector_t *p, struct vector_t *n, struct vector_t *u, double s) {
  
  struct vector_t r;

  struct vector_t *a, *b, *c, *n1, *n2, *n3;

  vector_cross(&r, n, u);
  
  if ( 1 ) {

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

  }

  if ( 1 ) {
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
}

struct vertex_array_t *cube(struct vector_t *p0, double s) {
  struct vertex_array_t *va = vertex_array_new(12*3);

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
  return va;
}

struct state_t game_state;

void mouse(int button, int state, int x, int y) {
  if ( button == 0 ) {
    game_state.px = x;
    game_state.py = y;
    game_state.button_down = state == 0;
  }
}

void motion(int x, int y) {
  if ( game_state.button_down ) {
    game_state.a1 += (x - game_state.px) / 100.0;
    game_state.a2 += (y - game_state.py) / 100.0;
    glutPostRedisplay();
  }
  game_state.px = x;
  game_state.py = y;
}

void key_up(unsigned char key, int x, int y) {
  switch(key) {
  case 'a':
    game_state.mx = 0;
    break;
  case 'd':
    game_state.mx = 0;
    break;
  case 'w':
    game_state.mz = 0;
    break;
  case 's':
    game_state.mz = 0;
    break;
  }
}

void key_down(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    game_state.quit = 1;
    break;
  case 'a':
    game_state.mx = 1;
    break;
  case 'd':
    game_state.mx = -1;
    break;
  case 'w':
    game_state.mz = 1;
    break;
  case 's':
    game_state.mz = -1;
    break;
  }
}

void time_minus(double *dt, struct timespec *after, struct timespec *before) {
  *dt = after->tv_sec - before->tv_sec;
  *dt += (after->tv_nsec - before->tv_nsec) / 1e9;
}

void anim() {
  struct timespec now;
  double dt;

  clock_gettime(CLOCK_REALTIME, &now);
  time_minus(&dt, &now, &game_state.last_update);
  dt *= 5;

  vector_plus(&game_state.pos, &game_state.pos, dt * game_state.mx, &game_state.left);
  vector_plus(&game_state.pos, &game_state.pos, dt * game_state.mz, &game_state.fow);

  game_state.last_update = now;
}

void gl_vertex(struct vector_t *v) {
  glVertex4d(v->v[0], v->v[1], v->v[2], v->v[3]);
}

void gl_normal(struct vector_t *v) {
  glNormal3d(v->v[0]/v->v[3], v->v[1]/v->v[3], v->v[2]/v->v[3]);
}

void vertex_array_draw(struct vertex_array_t *f) {
  int i;
  struct vector_t *n, *v;

  n = f->n;
  v = f->v;

  glBegin(GL_TRIANGLES);
  for(i=0; i<f->tail; i++) {
    gl_normal(n);
    gl_vertex(v);
    ++n;
    ++v;
  }
  glEnd();

  #if 0
  struct vector_t v2;
  v = f->v;
  n = f->n;
  glBegin(GL_LINES);
  for(i=0; i<f->tail; ++i) {
    gl_vertex(v);
    vector_plus(&v2, v, 5.0, n);
    gl_vertex(&v2);
    ++v, ++n;
  }
  glEnd();
  #endif

  
}

double vx(struct vector_t *v) {
  return v->v[0] / v->v[3];
}

double vy(struct vector_t *v) {
  return v->v[1] / v->v[3];
}

double vz(struct vector_t *v) {
  return v->v[2] / v->v[3];
}

void print_vector(char *name, struct vector_t *v) {
  printf("%s: %02.2f %02.2f %02.2f\n", name, v->v[0]/v->v[3], v->v[1]/v->v[3], v->v[2]/v->v[3]);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  struct fvector_t fpos, ffow;
  struct vector_t  *pos    = &game_state.pos;
  struct vector_t  *fow    = &game_state.fow;
  struct vector_t  *up     = &U1;
  struct vector_t  cosu, sinu, center, sinf, cosf;

  vector_times(&cosu, &U0, cos(game_state.a1));
  vector_times(&sinu, &U2, sin(game_state.a1));

  vector_plus(fow, &cosu, 1.0, &sinu);

  vector_times(&cosf, fow, cos(game_state.a2));
  vector_times(&sinf, &U1, sin(game_state.a2));

  vector_plus(fow, &cosf, 1.0, &sinf);

  vector_plus(&center, pos, 5.0, fow);

  vector_cross(&game_state.left, up, fow);

  gluLookAt(
            vx(pos),     vy(pos),     vz(pos),     // eye
            vx(&center), vy(&center), vz(&center), // center
            0.0,         1.0,         0.0          // up
  );

  fvector_copy_vector(&fpos, pos);
  fvector_copy_vector(&ffow, fow);

  glLightfv(GL_LIGHT0, GL_POSITION, fpos.v);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  COLOR_GRAY9);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  COLOR_GRAY2);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, COLOR_YELLOW);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, COLOR_YELLOW);
  // vertex_array_draw(game_state.box);

  vertex_array_draw(game_state.va);

  glutSwapBuffers();
}

void init(void) {

  game_state.quit = 0;
  game_state.box = cube(&ZERO, 5);
  game_state.va  = vertex_array_new(100000);
  game_state.field = spherical_density_field_new(&ZERO, 10);
  render_field(game_state.va, game_state.field, &ZERO, 0.5, 20);

  vector_set(&game_state.pos, 0, 0, -10);
  clock_gettime(CLOCK_REALTIME, &game_state.last_update);

  game_state.a1 = 0;
  game_state.a2 = 0;
  game_state.px = 0;
  game_state.py = 0;
  game_state.button_down = 0;

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glShadeModel(GL_SMOOTH);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0, 1.0, 1.0, 10000.0);
}

void fgDeinitialize( void );

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("red 3D lighted cube");
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(key_down);
  glutKeyboardUpFunc(key_up);
  init();

  while(! game_state.quit) {
    display();
    anim();
    glutMainLoopEvent();
  }

  fgDeinitialize();

  return 0;             /* ANSI C requires main to return int. */
}
