#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <vector>
#include <string>

void SDK_Import(std::string filepath, std::vector<int32_t>& mtx);
void SDK_Copy(std::vector<int32_t>& src, std::vector<int32_t>& dst);
void SDK_Print(std::vector<int32_t>& mtx);
void SDK_Pretty_Print(std::vector<int32_t>& mtx);
void SDK_Apply(std::vector<int32_t>& dst, std::vector<int32_t>& src);

#endif
