#include "vertical.h"

#include <assert.h>
#include <stdlib.h>
#include <vector>

#include "field.h"

bool SDK_Mark_Vertical_Availables(int32_t mtx[], int start_col, int end_col) {
    bool change = false;
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
        int32_t unused_numbers = result ^ ((1 << SIZE) - 1);
        for (int32_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[b * SIZE + a])) {
                int32_t old = mtx[b * SIZE + a];
                mtx[b * SIZE + a] &= unused_numbers;
                change |= (old != mtx[b * SIZE + a]);
                assert(mtx[b * SIZE + a] != 0);
            }
        }
    }
    return change;
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
        if (possible_twins_idx.size() < 2) {
          continue;
        }
        for (int i=0; i<possible_twins_idx.size()-1; i++) {
            for (int j=i+1; j<possible_twins_idx.size(); j++) {
                if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                    set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1]) {
                    // remove other values
                    int32_t old_1 = mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a];
                    int32_t old_2 = mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a];
                    mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    change |= (old_1 != mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a]) ||
                             (old_2 != mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a]);
                    break;
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Vertical_Availables_Triplets(int32_t mtx[], int start_col, int end_col) {
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
            if (set_bits[i].size() == 3) {
                possible_twins_idx.push_back(i);
            }
        }
        if (possible_twins_idx.size() < 3) {
          continue;
        }
        for (int i=0; i<possible_twins_idx.size()-2; i++) {
            for (int j=i+1; j<possible_twins_idx.size()-1; j++) {
                for (int k=j+1; k<possible_twins_idx.size(); k++) {
                    if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                        set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[k]][0] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[k]][1] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[j]][2] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[k]][2]) {
                        // remove other values
                        int32_t old_1 = mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a];
                        int32_t old_2 = mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a];
                        int32_t old_3 = mtx[set_bits[possible_twins_idx[i]][2] * SIZE + a];
                        mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        mtx[set_bits[possible_twins_idx[i]][2] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        change = change ||
                                (old_1 != mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a]) ||
                                (old_2 != mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a]) ||
                                (old_3 != mtx[set_bits[possible_twins_idx[i]][2] * SIZE + a]);
                        break;
                    }
                }
            }
        }
    }
    return change;
}
