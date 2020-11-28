#ifndef UTIL_HEADER
#define UTIL_HEADER

#include "defs.h"
#include <string>


void SDK_Import(std::string filepath, int32_t mtx[]);
void SDK_Copy(int32_t src[], int32_t dst[]);
void SDK_Print(int32_t mtx[]);
void SDK_Pretty_Print(int32_t mtx[]);
bool SDK_Apply(int32_t dst[], int32_t src[]);

#endif
