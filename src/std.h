#ifndef STD_H
#define STD_H

#define CHECK_RETURN(cond, ret) if ( cond ) { return ret; };
#define CHECK_GOTO(cond, error) if ( cond ) { goto error; };
#define MIN(x, y) (x <= y ? x : y)
#define MAX(x, y) (x >= y ? x : y)

#define RGBA(r, g, b, a) \
  ((r & 0xff) | (g & 0xff) << 8 | (b & 0xff) << 16 | (a & 0xff) << 24)

#endif
