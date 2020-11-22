#include "vertical.h"

#include <assert.h>
#include <stdlib.h>

#include "field.h"

void SDK_Mark_Vertical_Availables(std::vector<int64_t>& mtx) {
    assert(mtx.size() != 0);
    for (int64_t a = 0; a < SIZE; ++a) {
        //  Find used numbers
        int64_t result = 0;
        for (int64_t b = 0; b < SIZE; ++b) {
            int64_t field = mtx[b * SIZE + a];
            if (is_field_literal(field)) {
                result |= field;
            }
        }

        //  Insert unused numbers to empty fields
        int64_t unused_numbers = result ^ 0b111111111;
        for (int64_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[b * SIZE + a])) {
                mtx[b * SIZE + a] &= unused_numbers;
                assert(mtx[b * SIZE + a] != 0);
            }
        }
    }
}
