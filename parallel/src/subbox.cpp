#include "subbox.h"

#include <stdlib.h>
#include <vector>

#include "field.h"

bool SDK_Mark_Subbox_Availables(int32_t mtx[], int start_box_idx, int end_box_idx) {
    bool change = false;
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
        int32_t unused_numbers = result ^ ((1 << SIZE) - 1);
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                if (!is_field_literal(mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d])) {
                    int32_t old = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                    mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] &= unused_numbers;
                    change |= (old != mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d]);
                }
            }
        }
    }
    return change;
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


bool SDK_Mark_Subbox_Availables_Twins(int32_t mtx[], int start_box_idx, int end_box_idx) {
    bool change = false;
    for (int32_t box = start_box_idx; box < end_box_idx; box++) {
        int32_t a = box / SIZE_MULTIPLIER;
        int32_t b = box % SIZE_MULTIPLIER;
        std::vector<std::vector<int>> set_bits(SIZE, std::vector<int>());
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    int count = 0;
                    while (field != 0 && count != SIZE) {
                        // check if the last bit is 1
                        if (field % 2 == 1) {
                            set_bits[count].push_back(c * SIZE + d);
                        }
                        count++;
                        field = field >> 1;
                    }
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
                    int32_t c1 = set_bits[possible_twins_idx[i]][0] / SIZE_MULTIPLIER;
                    int32_t d1 = set_bits[possible_twins_idx[i]][0] % SIZE_MULTIPLIER;
                    int32_t c2 = set_bits[possible_twins_idx[i]][1] / SIZE_MULTIPLIER;
                    int32_t d2 = set_bits[possible_twins_idx[i]][1] % SIZE_MULTIPLIER;
                    int32_t old_1 = mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]; 
                    int32_t old_2 = mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2];
                    mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                    change |= (old_1 != mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]) ||
                             (old_2 != mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2]);
                    break;
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Subbox_Availables_Triplets(int32_t mtx[], int start_box_idx, int end_box_idx) {
    bool change = false;
    for (int32_t box = start_box_idx; box < end_box_idx; box++) {
        int32_t a = box / SIZE_MULTIPLIER;
        int32_t b = box % SIZE_MULTIPLIER;
        std::vector<std::vector<int>> set_bits(SIZE, std::vector<int>());
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    int count = 0;
                    while (field != 0 && count != SIZE) {
                        // check if the last bit is 1
                        if (field % 2 == 1) {
                            set_bits[count].push_back(c * SIZE + d);
                        }
                        count++;
                        field = field >> 1;
                    }
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
                        int32_t c1 = set_bits[possible_twins_idx[i]][0] / SIZE_MULTIPLIER;
                        int32_t d1 = set_bits[possible_twins_idx[i]][0] % SIZE_MULTIPLIER;
                        int32_t c2 = set_bits[possible_twins_idx[i]][1] / SIZE_MULTIPLIER;
                        int32_t d2 = set_bits[possible_twins_idx[i]][1] % SIZE_MULTIPLIER;
                        int32_t c3 = set_bits[possible_twins_idx[i]][2] / SIZE_MULTIPLIER;
                        int32_t d3 = set_bits[possible_twins_idx[i]][3] % SIZE_MULTIPLIER;
                        int32_t old_1 = mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]; 
                        int32_t old_2 = mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2];
                        int32_t old_3 = mtx[((a * SIZE_MULTIPLIER) + c3) * SIZE + (b * SIZE_MULTIPLIER) + d3];
                        mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        mtx[((a * SIZE_MULTIPLIER) + c3) * SIZE + (b * SIZE_MULTIPLIER) + d3] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                        change = change ||
                                (old_1 != mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]) ||
                                (old_2 != mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2]) ||
                                (old_3 != mtx[((a * SIZE_MULTIPLIER) + c3) * SIZE + (b * SIZE_MULTIPLIER) + d3]);
                        break;
                    }
                }
            }
        }
    }
    return change;
}
