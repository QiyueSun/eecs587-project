#include <assert.h>
#include "field.h"

bool is_field_literal(int32_t field) {
    if (field == 0)
        return false;
    if (((field - 1) & field) == 0) 
        return true;
    return false;
}

bool is_field_empty(int32_t field) {
    return field == 0;
}

int32_t to_pretty(int32_t field) {
  if (!is_field_literal(field)) {
    return 0;
  }
  if (field == 1) return 1;
    int32_t result = 0;
    if (((field + 1) & field) == 0) 
        return 0;
    while (field != 0) {
        field = field >> 1;
        result++;
    }
    return result;
}

int32_t translate_field(int32_t fld) {
    if (fld == 0) {
        return ~(fld & 0);
    }
    return 1 << (fld - 1);
}
