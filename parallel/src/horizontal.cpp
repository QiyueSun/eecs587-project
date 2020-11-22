#include "breakdown.h"

#include <assert.h>

#include "field.h"


void SDK_Mark_Horizontal_Availables(std::vector<std::vector<int64_t>> mtx) {
    assert(mtx.size() != 0);
    for (int64_t a = 0; a < SIZE; ++a) {
        int64_t result = 0;
        for (int64_t b = 0; b < SIZE; ++b) {

            int64_t field = mtx[a][b];
            if (is_field_literal(field)) {
                result |= field;
            }
        }
        
        //  Insert unused numbers to empty fields
        int64_t unused_numbers = result ^ 0b111111111;
        for (int64_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[a][b])) {
                mtx[a][b] &= unused_numbers;
                assert(mtx[a][b] != 0);
            }
        }
    }
}
