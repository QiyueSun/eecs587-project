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


bool SDK_Mark_Vertical_Availables_Twins(int32_t mtx[], int start_col, int end_col) {
    bool change = false;
    for (int32_t a = start_col; a < end_col; a++) {
        std::vector<std::vector<int>> set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[b * SIZE + a];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1) {
                        set_bits[count].push_back(b);
                    }
                    count++;
                    field = field >> 1;
                }
            }
        }
        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 2) {
                possible_twins_idx.push_back(i);
            }
        }
        for (int i=0; i<possible_twins_idx.size()-1; i++) {
            for (int j=i+1; j<possible_twins_idx.size(); j++) {
                if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                    set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1]) {
                    // remove other values
                    mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    change = true;
                    break;
                }
            }
        }
    }
    return change;
}
