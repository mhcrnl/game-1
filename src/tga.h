#ifndef TGA_H
#define TGA_H

#include "image.h"

struct tga_hdr_t {
  uint8_t  id_len;
  uint8_t  color_map_type;
  uint8_t  image_type;
  uint16_t color_map_offset;
  uint16_t color_map_len;
  uint8_t  color_map_entry_size;
  uint16_t  x;
  uint16_t  y;
  uint16_t  width;
  uint16_t  height;
  uint8_t   depth;
  uint8_t   descriptor;
} __attribute__ ((packed));

struct image_t *new_image(uint32_t width, uint32_t height);
struct image_t *load_tga(char *filename);

#endif
