#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <vector>
#include <string>

void SDK_Import(std::string filepath, std::vector<std::vector<int64_t>>& mtx);
void SDK_Copy(std::vector<std::vector<int64_t>> src, std::vector<std::vector<int64_t>> dst);
void SDK_Print(std::vector<std::vector<int64_t>> mtx);
void SDK_Pretty_Print(std::vector<std::vector<int64_t>> mtx);
// void SDK_Apply(std::vector<std::vector<int64_t>> dst, std::vector<std::vector<int64_t>> src);
void SDK_Apply(std::vector<std::vector<int64_t>> dst, int64_t src[]);

#endif
