#include <assert.h>
#include "field.h"

bool is_field_literal(int64_t field) {
    if (((field + 1) & field) == 0) 
        return false;
    assert((field & (field-1)) == 0);
    return true;
}

bool is_field_empty(int64_t field) {
    return field == 0;
}

int64_t to_pretty(int64_t field) {
    int64_t result = 0;
    if (((field + 1) & field) == 0) 
        return 0;
    while (field != 0) {
        field = field >> 1;
        result++;
    }
    return result;
}

int64_t translate_field(int64_t fld) {
    if (fld == 0) {
        return ~(fld & 0);
    }
    return 1 << (fld - 1);
}
