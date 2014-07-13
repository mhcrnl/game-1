#include "tga.h"

#include "std.h"
#include "new.h"
#include "image.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct image_t *load_tga(char *filename) {
  int fd, status;
  struct tga_hdr_t hdr;
  struct image_t   *img;
  char label[256];
  uint8_t buf[4*1024];

  fd = open(filename, 0);
  CHECK_RETURN(fd <= 0, 0);

  status = read(fd, &hdr, sizeof(hdr));
  CHECK_RETURN(status != sizeof(hdr), 0);

  CHECK_RETURN(hdr.color_map_type != 0, 0); 
  CHECK_RETURN(hdr.image_type != 2, 0);

  if ( hdr.id_len > 0 ) {
    status = read(fd, label, hdr.id_len);
    CHECK_RETURN(status != hdr.id_len, 0);
  }

  CHECK_RETURN(hdr.color_map_len != 0, 0);
  CHECK_RETURN(hdr.depth != 24, 0);

  img = new_image(hdr.width, hdr.height);

  int bytes_left = (hdr.width * hdr.height * hdr.depth) / 8;

  int i = 0, p, q;
  int buf_off = 0;

  while(bytes_left > 0) {
    int bytes_read = read(fd, buf + buf_off, MIN(bytes_left, sizeof(buf)-buf_off));
    for(p=0; p + 3 <= bytes_read + buf_off; ) {
      img->data[i++] = buf[p++];
      img->data[i++] = buf[p++];
      img->data[i++] = buf[p++];
      img->data[i++] = 0xff;
    }

    for(q=0; p+q < bytes_read + buf_off; ++q) {
      buf[q] = buf[p+q];
    }

    buf_off = q;
    bytes_left -= bytes_read;
  }
    
  return img;
}

