#include "subbox.h"

#include <stdlib.h>

#include "field.h"

void SDK_Mark_Subbox_Availables(int32_t mtx[], int start_box_idx, int end_box_idx) {
    for (int32_t i = start_box_idx; i < end_box_idx; i++) {
        int32_t a = i / SIZE_MULTIPLIER;
        int32_t b = i % SIZE_MULTIPLIER;
        //  Find used numbers
        int32_t result = 0;
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (is_field_literal(field)) {
                    result |= field;
                }
            }
        }

        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ 0b111111111;
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                if (!is_field_literal(mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d])) {
                    mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] &= unused_numbers;
                }
            }
        }
    }
}
