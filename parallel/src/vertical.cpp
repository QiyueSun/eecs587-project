#include "vertical.h"

#include <assert.h>
#include <stdlib.h>

#include "field.h"

void SDK_Mark_Vertical_Availables(int32_t mtx[SIZE*SIZE]) {
    for (int32_t a = 0; a < SIZE; ++a) {
        //  Find used numbers
        int32_t result = 0;
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[b * SIZE + a];
            if (is_field_literal(field)) {
                result |= field;
            }
        }

        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ 0b111111111;
        for (int32_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[b * SIZE + a])) {
                mtx[b * SIZE + a] &= unused_numbers;
                assert(mtx[b * SIZE + a] != 0);
            }
        }
    }
}
