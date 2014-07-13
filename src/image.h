#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

struct image_t {
  uint32_t width;
  uint32_t height;
  uint8_t *data;
};

struct image_t *new_image(uint32_t width, uint32_t height);
void free_image(struct image_t *img);

#endif
