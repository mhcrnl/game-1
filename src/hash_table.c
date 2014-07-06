#include "hash_table.h"
#include "new.h"
#include <string.h>

#define HASH_TABLE_DIRTY_FLAG 0x2
#define HASH_TABLE_OCCUPIED_FLAG 0x1

#ifdef LITTLE_ENDIAN
#define HASH_MASK_1 0xff
#define HASH_MASK_2 0xffff
#define HASH_MASK_3 0xffffff
#else
#define HASH_MASK_1 0xff000000
#define HASH_MASK_2 0xffff0000
#define HASH_MASK_3 0xffffff00
#endif

static inline uint8_t hash_table_is_dirty(
  struct hash_table_t *ht,
  int32_t index
) {
  return ht->flags[index] & HASH_TABLE_DIRTY_FLAG;
}

static inline uint8_t hash_table_is_occupied(
  struct hash_table_t *ht,
  int32_t index
) {
  return ht->flags[index] & HASH_TABLE_OCCUPIED_FLAG;
}

static inline void hash_table_set_dirty(
  struct hash_table_t *ht,
  int32_t index
) {
  ht->flags[index] |= HASH_TABLE_DIRTY_FLAG;
}

static inline void hash_table_set_occupied(
  struct hash_table_t *ht,
  int32_t index
) {
  ht->flags[index] |= HASH_TABLE_OCCUPIED_FLAG;
}

static inline void* hash_table_key( 
  struct hash_table_t *ht,
  uint32_t index
) {
  return ht->keys + (index * ht->key_size);
}

static inline int32_t hash_table_key_eq(
  struct hash_table_t *ht,
  uint32_t index,
  void *key
) {
  uint32_t len = ht->key_size;
  int32_t *key1 = hash_table_key(ht, index);
  int32_t *key2 = key;
  while ( len > 4 ) {
    if ( *key1 != *key2 ) {
      return 0;
    }
    len -= 4;
    key1 += 1;
    key2 += 1;
  }
  if ( len == 0 ) {
    return 1;
  } else if ( len == 1 ) {
    return (*key1 & HASH_MASK_1) == (*key2 & HASH_MASK_2);
  } else if ( len == 2 ) {
    return (*key1 & HASH_MASK_2) == (*key2 & HASH_MASK_2);
  } else {
    return (*key1 & HASH_MASK_3) == (*key2 & HASH_MASK_3);
  }
}

static inline void* hash_table_value( 
  struct hash_table_t *ht,
  uint32_t index
) {
  return ht->values + (index * ht->value_size);
}

void hash_table_init(
  struct hash_table_t *ht, 
  uint32_t key_size, 
  uint32_t value_size, 
  uint32_t len
) {
  ht->key_size = key_size;
  ht->value_size = value_size;
  ht->occupied = 0;
  ht->len = len;
  ht->keys = malloc(len*key_size);
  ht->values = malloc(len*value_size);
  ht->flags = malloc(len);
}

struct hash_table_t *hash_table_new(
  uint32_t key_size, 
  uint32_t value_size, 
  uint32_t len
) {
  struct hash_table_t *ht = NEW(struct hash_table_t);
  hash_table_init(ht, key_size, value_size, len);
  return ht;
}

static inline void hash_table_grow(struct hash_table_t *ht) {
  struct hash_table_t nht;
  uint32_t index;
  hash_table_init(&nht, ht->key_size, ht->value_size, ht->len*2);
  for(index=0; index<ht->len; ++index) {
    if ( hash_table_is_occupied(ht, index) ) {
      uint8_t *key = hash_table_key(ht, index);
      uint8_t *value = hash_table_value(ht, index);
      hash_table_insert(ht, key, value);
    }
  }
  free(ht->keys);
  free(ht->values);
  free(ht->flags);
  ht->keys = nht.keys;
  ht->values = nht.values;
  ht->flags = nht.flags;
  ht->len = nht.len;
  ht->occupied = nht.occupied;
}

static inline void hash_table_assign_value(struct hash_table_t *ht, uint32_t index, void *value) {
  memcpy(ht->values + (index * ht->value_size), value, ht->value_size);
}

uint32_t hash_table_hash_value(
  uint32_t key_size, 
  uint8_t  *key
) {
  uint32_t r = 0, i;
  for(i=0;i<key_size;++i) {
    r ^= key[i] << (i % 4);
  }
  return r;
}
 
void hash_table_insert(
  struct hash_table_t *ht,
  void *key, 
  void *value
) {
  if ( ht->occupied * 4 > ht->len * 3 ) {
    hash_table_grow(ht);
  }
  uint32_t index = hash_table_hash_value(ht->key_size, key);
  while(1) {
    if ( hash_table_key_eq(ht, index, key) ) {
      if ( ! hash_table_is_occupied(ht, index) ) {
        ht->occupied += 1;
        hash_table_set_occupied(ht, index);
      }
      hash_table_assign_value(ht, index, value);
      return;
    } else if ( ! hash_table_is_occupied(ht, index) && ! hash_table_is_dirty(ht, index) ) {
      ht->occupied += 1;
      hash_table_set_occupied(ht, index);
      hash_table_assign_value(ht, index, value);
      return;
    } else {
      hash_table_set_dirty(ht, index);
      index = (index + 1) & ht->len;
    }
  }
}

void* hash_table_lookup(
  struct hash_table_t *ht,
  void *key
) {
  uint32_t index = hash_table_hash_value(ht->key_size, key);
  while(1) {
    if ( hash_table_key_eq(ht, index, key) == 0 ) {
      return hash_table_value(ht, index);
    } else if ( hash_table_is_dirty(ht, index) ) {
      index = (index + 1) % ht->len ;
    } else {
      return 0;
    }
  }
}


