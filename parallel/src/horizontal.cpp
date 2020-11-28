#include "breakdown.h"

#include <assert.h>
#include <vector>

#include "field.h"


void SDK_Mark_Horizontal_Availables(int32_t mtx[], int start_row, int end_row) {
    for (int32_t a = start_row; a < end_row; ++a) {
        int32_t result = 0;
        for (int32_t b = 0; b < SIZE; ++b) {

            int32_t field = mtx[a * SIZE + b];
            if (is_field_literal(field)) {
                result |= field;
            }
        }
        
        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ 0b111111111;
        for (int32_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[a * SIZE + b])) {
                mtx[a * SIZE + b] &= unused_numbers;
                assert(mtx[a * SIZE + b] != 0);
            }
        }
    }
}


bool SDK_Mark_Horizontal_Availables_Long_Ranger(int32_t mtx[], int start_row, int end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; ++a) {
        int32_t result = 0;
        std::vector<int> set_bits(SIZE, 0);
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
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
                    int32_t field = mtx[a * SIZE + b];
                    if (!is_field_literal(field)) {
                        field = field >> i;
                        if (field % 2 == 1) {
                            mtx[a * SIZE + b] = 1 << i;
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
