#ifndef MESH_H
#define MESH_h

#include "std.h"

struct mesh_t {
  uint8_t is_skel;
};



struct chunk_hdr_t {
  uint16_t chunk_id;
  uint16_t len;
};

void load_mesh(char *filename);

#endif
