#ifndef MESH_H
#define MESH_h

#include "std.h"
#include "list.h"

struct mesh_node_t {
  uint32_t chunk_it;
  uint8_t is_skel;
  struct list_t nodes;
};

struct mesh_t {
};

struct chunk_hdr_t {
  uint16_t id;
  uint16_t len;
};

struct mesh_t* load_mesh(char *filename);

#endif
