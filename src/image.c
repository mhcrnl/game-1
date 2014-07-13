#include "image.h"
#include "std.h"
#include "new.h"


struct image_t *new_image(uint32_t width, uint32_t height) {
  struct image_t *img = NEW(struct image_t);
  img->width  = width;
  img->height = height;
  img->data   = NEW_ARRAY(uint8_t, 4 * width * height);
  return img;
}

void free_image(struct image_t *img) {
  free(img->data);
  free(img);
}

