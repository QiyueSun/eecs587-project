#include "util.h"
#include "defs.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "field.h"

using namespace std;

void bit_print(int32_t kMATRIX[])
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      cout << std::bitset<16>(kMATRIX[i * SIZE + j]) << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void SDK_Import(string filepath, int32_t mtx[])
{
  ifstream file;
  file.open(filepath);
  int row_idx = 0;
  while (!file.eof())
  {
    string line;
    getline(file, line);
    int prev = 0, col_idx = 0;
    int i = prev;
    while (i < line.size())
    {
      for (; i < line.size(); i++)
      {
        if (line[i] == ' ')
          break;
      }
      int num = stoi(line.substr(prev, i));
      mtx[row_idx * SIZE + col_idx] = translate_field(num);
      i++;
      prev = i;
      col_idx++;
    }
    row_idx++;
  }
  file.close();
}

void SDK_Copy(int32_t src[], int32_t dst[])
{
  for (int32_t a = 0; a < SIZE; a++)
  {
    for (int32_t b = 0; b < SIZE; b++)
    {
      dst[a * SIZE + b] = src[a * SIZE + b];
    }
  }
}

void SDK_Print(int32_t mtx[])
{
  for (int32_t a = 0; a < SIZE; a++)
  {
    for (int32_t b = 0; b < SIZE; b++)
    {
      printf("%d ", mtx[a * SIZE + b]);
    }
    printf("\n");
  }
}

void SDK_Pretty_Print(int32_t mtx[])
{
  for (int32_t a = 0; a < SIZE; a++)
  {
    for (int32_t b = 0; b < SIZE; b++)
    {
      printf("%d ", to_pretty(mtx[a * SIZE + b]));
    }
    printf("\n");
  }
}

/*
  return change or not
*/
bool SDK_Apply(int32_t dst[], int32_t src[])
{
  bool change = false;
  for (int32_t a = 0; a < SIZE; a++)
  {
    for (int32_t b = 0; b < SIZE; b++)
    {
      int32_t old = dst[a * SIZE + b];
      dst[a * SIZE + b] &= src[a * SIZE + b];
      if (dst[a * SIZE + b] != old)
      {
        change = true;
      }
    }
  }
  return change;
}

bool find_permus(int32_t mtx_copy[], std::vector<int32_t*>& stack, 
                 std::vector<std::vector<int32_t> >& index_value_map,
                 std::vector<bool>& available_value,
                 int32_t i, int32_t start_cell_idx, int32_t end_cell_idx) {
    if (i >= end_cell_idx-start_cell_idx) {
        return true;
    }
    if (!index_value_map[i].empty()) {
        int j = 0;
        int32_t old = mtx_copy[start_cell_idx + i];
        for (; j<index_value_map[i].size(); j++) {
            if (available_value[index_value_map[i][j] - 1]) {
                mtx_copy[start_cell_idx + i] = 1 << (index_value_map[i][j]-1);
                available_value[index_value_map[i][j] - 1] = false;
                bool result = find_permus(mtx_copy, stack, index_value_map, available_value, i+1, start_cell_idx, end_cell_idx);
                if (result) {
                    int32_t *mtx_perm = new int32_t[SIZE*SIZE];
                    memcpy(mtx_perm, mtx_copy, SIZE*SIZE*sizeof(int32_t));
                    stack.push_back(mtx_perm);
                    available_value[index_value_map[i][j] - 1] = true;
                    continue;
                }
                else {
                    available_value[index_value_map[i][j] - 1] = true;
                }
            }
        }
        if (j == index_value_map[i].size()) {
            mtx_copy[start_cell_idx + i] = old;
            return false;
        }
    }
    return find_permus(mtx_copy, stack, index_value_map, available_value, i+1, start_cell_idx, end_cell_idx);
}

void SDK_Permutations(int32_t mtx[], std::vector<int32_t*>& stack, int32_t start_cell_idx, int32_t end_cell_idx) {
    std::vector<std::vector<int32_t> > index_value_map(end_cell_idx-start_cell_idx, std::vector<int32_t>());
    std::vector<bool> available_value(SIZE, false);
    int literal_fixed = 0;
    for (int i=start_cell_idx; i<end_cell_idx; i++) {
        int32_t field = mtx[i];
        // cout << field << endl;
        if (!is_field_literal(field)) {
        int count = 0;
        while (field != 0 && count != SIZE) {
            if (field % 2 == 1) {
            index_value_map[i - start_cell_idx].push_back(count+1);
            available_value[count] = true;
            }
            count++;
            field = field >> 1;
        }
        }
        else {
        literal_fixed++;
        }
    }
    // cout << "literal_fixed = " << literal_fixed << endl;
    // cout << "index_value_map:" << endl;
    // for (int i=0; i<end_cell_idx-start_cell_idx; i++) {
    //     for (int j=0; j<index_value_map[i].size(); j++) {
    //         cout << index_value_map[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "available_value:" << endl;
    // for (int i=0; i<available_value.size(); i++) {
    //     cout << available_value[i] << " ";
    // }
    // cout << endl;
    int32_t mtx_copy[SIZE*SIZE];
    memcpy(mtx_copy, mtx, SIZE*SIZE*sizeof(int32_t));
    // for loop all the possible values to get permutations
    find_permus(mtx_copy, stack, index_value_map, available_value, 0, start_cell_idx, end_cell_idx);
    // cout << "stack size = " << stack.size() << endl;
}
