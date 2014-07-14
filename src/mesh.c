#include "mesh.h"
#include "std.h"
#include "new.h"
#include <stdio.h>

struct chunk_t {
  struct chunk_hdr_t hdr;
};

int read_chunk_hdr(int fd, struct chunk_hdr_t *hdr) {
  int num_read;

  num_read = read(fd, hdr, sizeof(*hdr));
  CHECK_RETURN(num_read != sizeof(*hdr), -EINVAL);
  CHECK_RETURN(hdr->len < sizeof(*hdr), -EINVAL);
  CHECK_RETURN(hdr->len > 1024*1024, -EINVAL);
  return 0;
}

struct mesh_t* new_mesh() {
  return NEW(struct mesh_t);
}

void delete_mesh(struct mesh_t *mesh) {
  free(mesh);
}

void free_mesh(struct mesh_t *mesh) {
  free(mesh);
}

struct mesh_t* load_mesh(char *filename) {
  int fd, pos;
  struct mesh_t *mesh;
  struct chunk_hdr_t chunk_hdr;

  fd = open(filename, 0);
  CHECK_RETURN(fd < 0, 0); 

  mesh = NEW(struct mesh_t);
  CHECK_GOTO(read_chunk_hdr(fd, &chunk_hdr), error);

  pos = sizeof(chunk_hdr);
  while(pos < chunk_hdr.len) {
    /* up to here */
  }

 error:
  if ( mesh != 0 ) {
    delete_mesh(mesh);
  }
  return 0;
}

void print_chunk(struct chunk_t *chunk) {
  switch(chunk->hdr.id) {
  case 0x1000:
    printf("HEADER %d:\n", chunk->hdr.len);
  case 0x3000:
    printf("MESH %d:\n", chunk->hdr.len);
  }
}
