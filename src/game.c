#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "game.h"
#include "cube.h"
#include "vertex_array.h"
#include "new.h"
#include "marching_cubes.h"
#include "draw.h"
#include "grid.h"

void glutLeaveMainLoop();

float COLOR_RED[]      = {1.0, 0.0, 0.0, 1.0};  
float COLOR_YELLOW[]   = {1.0, 1.0, 0.0, 1.0};  
float COLOR_WHITE[]    = {1.0, 1.0, 1.0, 1.0};  
float COLOR_GRAY2[]     = {0.2, 0.2, 0.2, 1.0};  
float COLOR_GRAY9[]     = {0.9, 0.9, 0.9, 1.0};  

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

void print_vector(char *name, struct vector_t *v) {
  printf("%s: %02.2f %02.2f %02.2f\n", name, v->v[0]/v->v[3], v->v[1]/v->v[3], v->v[2]/v->v[3]);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  struct fvector_t light_pos;
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

  fvector_set(&light_pos, -10, -10, -10);
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos.v);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  COLOR_GRAY9);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  COLOR_GRAY2);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, COLOR_YELLOW);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, COLOR_YELLOW);
  // vertex_array_draw(game_state.box);

  // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  vertex_array_draw_tri(game_state.va_tri);
  vertex_array_draw_lines(game_state.va_lines);

  glutSwapBuffers();
}

void init(void) {

  game_state.quit = 0;
  game_state.box = vertex_array_new(36);
  cube(game_state.box, &ZERO, 5);
  game_state.va_tri  = vertex_array_new(100000);
  game_state.va_lines  = vertex_array_new(100000);
  game_state.field = spherical_density_field_new(&ZERO, 10);
  render_field(game_state.va_tri, game_state.va_lines, game_state.field, &ZERO, 2, 20);
  //  render_grid(game_state.va_lines, &ZERO, 0.5, 20);

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
