#ifndef FIELD_HEADER
#define FIELD_HEADER

#include <stdint.h>
#include <stdbool.h>

bool is_field_literal(int64_t field);
bool is_field_empty(int64_t field);

int64_t to_pretty(int64_t field);
int64_t translate_field(int64_t field);

#endif
