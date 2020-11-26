#ifndef UTIL_HEADER
#define UTIL_HEADER

#include "defs.h"
#include <string>


void SDK_Import(std::string filepath, int32_t mtx[SIZE*SIZE]);
void SDK_Copy(int32_t src[SIZE*SIZE], int32_t dst[SIZE*SIZE]);
void SDK_Print(int32_t mtx[SIZE*SIZE]);
void SDK_Pretty_Print(int32_t mtx[SIZE*SIZE]);
void SDK_Apply(int32_t dst[SIZE*SIZE], int32_t src[SIZE*SIZE]);

#endif
