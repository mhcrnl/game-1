#include "ds.h"
#include "std.h"
#include "list.h"
#include "new.h"

struct chunk_hdr_t {
  uint16_t id;
  uint32_t len;
};

struct chunk_t {
  struct chunk_hdr_t hdr;
  struct list_t ns;
};

struct chunk_t* new_chunk() {
  struct chunk_t *chunk = NEW(struct chunk_t);
  list_init(&chunk->ns, sizeof(struct chunk_t *), 5);
  return chunk;
}

struct chunk_t* load_chunk(int fd, uint32_t *pos) {
  struct chunk_t *chunk = new_chunk();
  uint32_t top = *pos;
  *pos += read(fd, &chunk->hdr, sizeof(chunk->hdr));
  while(*pos < top + chunk->hdr.len) {
    list_push(&chunk->ns, load_chunk(fd, pos));
  }
  return chunk;
}

struct model_t *load_ds(char *filename) {

  int fd;
  uint32_t pos = 0;
  struct model_t *model;
  struct chunk_hdr_t hdr;
  struct chunk_t *root;

  fd = open(filename, 0);
  CHECK_RETURN(fd < 0, 0);

  read(fd, &hdr, sizeof(hdr));

  model = new_model();
  root = load_chunk(fd, &pos);

  return model;
}
