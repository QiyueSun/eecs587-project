#ifndef HORIZONTAL_HEADER
#define HORIZONTAL_HEADER

#include "defs.h"

bool SDK_Mark_Horizontal_Availables(int32_t mtx[], bool& assert_fail, int32_t start_row, int32_t end_row);
bool SDK_Mark_Horizontal_Availables_Long_Ranger(int32_t mtx[], int start_row, int end_row);
bool SDK_Mark_Horizontal_Availables_Twins(int32_t mtx[], int start_row, int end_row);
bool SDK_Mark_Horizontal_Availables_Triplets(int32_t mtx[], int start_row, int end_row);

#endif
