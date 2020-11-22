#include "subbox.h"

#include <assert.h>
#include <stdlib.h>

#include "field.h"

void SDK_Mark_Subbox_Availables(std::vector<int64_t>& mtx) {
    assert(mtx.size() != 0);

    for (int64_t a = 0; a < SIZE_MULTIPLIER; ++a) {
        for (int64_t b = 0; b < SIZE_MULTIPLIER; ++b) {
            //  Find used numbers
            int64_t result = 0;
            for (int64_t c = 0; c < SIZE_MULTIPLIER; ++c) {
                for (int64_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                    int64_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                    if (is_field_literal(field)) {
                        result |= field;
                    }
                }
            }

            //  Insert unused numbers to empty fields
            int64_t unused_numbers = result ^ 0b111111111;
            for (int64_t c = 0; c < SIZE_MULTIPLIER; ++c) {
                for (int64_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                    if (!is_field_literal(mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d])) {
                        mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] &= unused_numbers;
                    }
                }
            }
        }
    }
}
