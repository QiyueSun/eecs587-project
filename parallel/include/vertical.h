#ifndef VERTICAL_HEADER
#define VERTICAL_HEADER

#include "defs.h"

bool SDK_Mark_Vertical_Availables(int32_t mtx[], bool& assert_fail, int32_t start_col, int32_t end_col);
bool SDK_Mark_Vertical_Availables_Long_Ranger(int32_t mtx[], int32_t start_col, int32_t end_col);
bool SDK_Mark_Vertical_Availables_Twins(int32_t mtx[], int start_col, int end_col);
bool SDK_Mark_Vertical_Availables_Triplets(int32_t mtx[], int start_col, int end_col);

#endif
