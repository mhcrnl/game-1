#include "model.h"
#include "new.h"

struct model_t *new_model() {
  struct model_t *model = NEW(struct model_t);
  return model;
}
