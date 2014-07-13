#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"
#include "std.h"

struct texture_t {
  uint32_t tex_id;
};

struct texture_t *new_texture(struct image_t *img);
void free_texture(struct image_t *texture);

#endif
