#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <vector>
#include <string>

void SDK_Import(std::string filepath, std::vector<int64_t>& mtx);
void SDK_Copy(std::vector<int64_t>& src, std::vector<int64_t>& dst);
void SDK_Print(std::vector<int64_t>& mtx);
void SDK_Pretty_Print(std::vector<int64_t>& mtx);
void SDK_Apply(std::vector<int64_t>& dst, std::vector<int64_t>& src);

#endif
