#include "vertical.h"

#include <assert.h>
#include <stdlib.h>
#include <vector>

#include "field.h"

void SDK_Mark_Vertical_Availables(int32_t mtx[], int start_col, int end_col) {
    for (int32_t a = start_col; a < end_col; ++a) {
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

bool SDK_Mark_Vertical_Availables_Long_Ranger(int32_t mtx[], int start_col, int end_col) {
    bool change = false;
    for (int32_t a = start_col; a < end_col; ++a) {
        int32_t result = 0;
        std::vector<int> set_bits(SIZE, 0);
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[b * SIZE + a];
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
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i] == 1) {
                for (int32_t b = 0; b < SIZE; ++b) {
                    int32_t field = mtx[b * SIZE + a];
                    if (!is_field_literal(field)) {
                        field = field >> i;
                        if (field % 2 == 1) {
                            mtx[b * SIZE + a] = 1 << i;
                            change = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return change;
}