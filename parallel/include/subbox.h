#ifndef SUBBOX_HEADER
#define SUBBOX_HEADER

#include "defs.h"

void SDK_Mark_Subbox_Availables(int32_t mtx[], int start_box_idx, int end_box_idx);
bool SDK_Mark_Subbox_Availables_Long_Ranger(int32_t mtx[], int start_box_idx, int end_box_idx);
bool SDK_Mark_Subbox_Availables_Twins(int32_t mtx[], int start_box_idx, int end_box_idx);

#endif
