#include "hash_table.h"
#include <assert.h>

int main() {
  struct hash_table_t *ht = hash_table_new(sizeof(int32_t), sizeof(int32_t), 10);
  int i;
  uint32_t key, value, *rvalue;

  for(i=0;i<20;++i) {
    key = i;
    value = i;
    hash_table_insert(ht, &key, &value);
    rvalue = (uint32_t *)hash_table_lookup(ht, &key);
    assert(value != 0);
    assert(value == *rvalue);
  }
  return 0;
}
