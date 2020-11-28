#include "breakdown.h"

#include <assert.h>
#include <vector>

#include "field.h"


bool SDK_Mark_Horizontal_Availables(int32_t mtx[], int start_row, int end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; ++a) {
        int32_t result = 0;
        for (int32_t b = 0; b < SIZE; ++b) {

            int32_t field = mtx[a * SIZE + b];
            if (is_field_literal(field)) {
                result |= field;
            }
        }
        
        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ ((1 << SIZE) - 1);
        for (int32_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[a * SIZE + b])) {
                int32_t old = mtx[a * SIZE + b];
                mtx[a * SIZE + b] &= unused_numbers;
                change |= (old != mtx[a * SIZE + b]);
                assert(mtx[a * SIZE + b] != 0);
            }
        }
    }
    return change;
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

bool SDK_Mark_Horizontal_Availables_Twins(int32_t mtx[], int start_row, int end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; a++) {
        std::vector<std::vector<int>> set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
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
                    int32_t old_1 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]];
                    int32_t old_2 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]];
                    mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    change |= (old_1 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]]) ||
                             (old_2 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]]);
                    break;
                }
            }
        }
    }
    return change;
}


bool SDK_Mark_Horizontal_Availables_Triplets(int32_t mtx[], int start_row, int end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; a++) {
        std::vector<std::vector<int>> set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
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
                        int32_t old_1 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]];
                        int32_t old_2 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]];
                        int32_t old_3 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][2]];
                        mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        mtx[a * SIZE + set_bits[possible_twins_idx[i]][2]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        change = change || 
                                (old_1 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]]) ||
                                (old_2 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]]) ||
                                (old_3 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][2]]);
                        break;
                    }
                }
            }
        }
    }
    return change;
}