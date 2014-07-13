#include "mesh.h"



struct chunk_t *read_chunk(int fd) {
  struct chunk_hdr_t hdr;
  struct chunk_t *chunk;
  int num_read;

  num_read = read(fd, &hdr, sizeof(hdr));
  CHECK_RETURN(num_read != sizeof(hdr), 0);
  CHECK_RETURN(hdr->len => sizeof(hdr), 0);
  CHECK_RETURN(hdr->len < 1024*1024, 0);

  chunk = (struct chunk_t *)malloc(sizeof(hdr));
  
}

struct mesh_t* load_mesh(char *filename) {
  int fd;
  struct chunk_t chunk;

  fd = open(filename, 0);
  CHECK_RETURN(fd < 0, 0); 

  read(fd, &chunk, sizeof(chunk));
  read(
  
  
}
