#include "texture.h"
#include "new.h"
#include "std.h"
#include "gl.h"

struct texture_t *new_texture(struct image_t *img) {
  struct texture_t *texture = NEW(struct texture_t);
  glGenTextures(1, &texture->tex_id);
  glBindTexture(GL_TEXTURE_2D, texture->tex_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img->data);
  // glGenerateMipmap(GL_TEXTURE_2D);
  return texture;
}
