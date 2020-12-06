#ifndef UTIL_HEADER
#define UTIL_HEADER

#include "defs.h"
#include <string>
#include <vector>
#include <mpi.h>


void bit_print(int32_t kMATRIX[]);
void SDK_Import(std::string filepath, int32_t mtx[]);
void SDK_Copy(int32_t dst[], int32_t src[]);
void SDK_Print(int32_t mtx[]);
void SDK_Pretty_Print(int32_t mtx[]);
bool SDK_Apply(int32_t dst[], int32_t src[]);
bool find_permus(int32_t mtx_copy[], std::vector<int32_t*>& stack, 
                 std::vector<std::vector<int32_t> >& index_value_map,
                 std::vector<bool>& available_value,
                 int32_t i, int32_t start_cell_idx, int32_t end_cell_idx);
void SDK_Permutations(int32_t mtx[], std::vector<int32_t*>& stack, int32_t start_cell_idx, int32_t end_cell_idx);
bool is_conflict(int32_t sudoku[]);
bool brute_force(int32_t mtx[], MPI_Request* request);

#endif
