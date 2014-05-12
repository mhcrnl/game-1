#ifndef NEW_H
#define NEW_H

#include <stdlib.h> // malloc

#define NEW(type) (type *)malloc(sizeof(type))
#define NEW_ARRAY(type, len) (type *)calloc(len, sizeof(type))

#endif

