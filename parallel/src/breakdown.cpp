#include <assert.h>
#include "breakdown.h"
#include "field.h"

bool SDK_Check_Breakdown(std::vector<std::vector<int64_t>> mtx) {
    assert(mtx.size() != 0);
    for (int64_t a = 0; a < SIZE; ++a) {
        for (int64_t b = 0; b < SIZE; ++b) {
            int64_t field = mtx[a][b];
            if (!is_field_literal(field)) {
                return false;
            }
        }
    }
    return true;
}
