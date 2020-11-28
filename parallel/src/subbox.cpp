#include "subbox.h"

#include <stdlib.h>
#include <vector>

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


bool SDK_Mark_Subbox_Availables_Long_Ranger(int32_t mtx[], int start_box_idx, int end_box_idx) {
    bool change = false;
    for (int32_t i = start_box_idx; i < end_box_idx; i++) {
        int32_t a = i / SIZE_MULTIPLIER;
        int32_t b = i % SIZE_MULTIPLIER;
        int32_t result = 0;
        std::vector<int> set_bits(SIZE, 0);
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    int count = 0;
                    while (field != 0 && count != SIZE) {
                        // check if the last bit is 1
                        if (field % 2 == 1) {
                            set_bits[count]++;
                        }
                        count++;
                        field = field >> 1;
                    }
                }
            }
        }

        for (int i=0; i<SIZE; i++) {
            if (set_bits[i] == 1) {
                for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
                    for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                        int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                        if (!is_field_literal(field)) {
                            field = field >> i;
                            if (field % 2 == 1) {
                                mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] = 1 << i;
                                change = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return change;
}