#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>

struct hash_table_t {
  uint32_t key_size;
  uint32_t value_size;
  uint32_t occupied;
  uint32_t len;
  uint8_t  *keys;
  uint8_t  *values;
  uint8_t  *flags;
};

void hash_table_init(
  struct hash_table_t *ht, 
  uint32_t key_size, 
  uint32_t value_size, 
  uint32_t len
);

struct hash_table_t *hash_table_new(
  uint32_t key_size, 
  uint32_t value_size, 
  uint32_t len
);

void hash_table_insert(
  struct hash_table_t *ht,
  void *key, 
  void *value
);

void* hash_table_lookup(
  struct hash_table_t *ht,
  void *key
);

#endif
