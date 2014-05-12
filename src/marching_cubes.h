#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#ifndef VECTOR_H
#include "vector.h"
#endif

struct cube_t {
  double          d[8];
  struct vector_t p[8];
};



#endif
