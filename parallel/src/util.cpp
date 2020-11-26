#include "util.h"
#include "defs.h"
#include <vector>
#include <string>
#include <fstream>

#include "field.h"

using namespace std;

void SDK_Import(string filepath, int32_t mtx[SIZE*SIZE]) {
    ifstream file;
    file.open(filepath);
    int row_idx = 0;
    while (!file.eof()) {
        string line;
        getline(file, line);
        int prev = 0, col_idx = 0;
        int i = prev;
        while (i < line.size()) {
            for (; i<line.size(); i++) {
                if (line[i] == ' ') break;
            }
            int num = stoi(line.substr(prev, i));
            mtx[row_idx * SIZE + col_idx] = translate_field(num);
            i++; prev = i; col_idx++;
        }
        row_idx++;
    }
    file.close();
}

void SDK_Copy(int32_t src[SIZE*SIZE], int32_t dst[SIZE*SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      dst[a * SIZE + b] = src[a * SIZE + b];
    }
  }
}

void SDK_Print(int32_t mtx[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      printf("%d ", mtx[a * SIZE + b]);
    }
    printf("\n");
  }
}

void SDK_Pretty_Print(int32_t mtx[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      printf("%d ", to_pretty(mtx[a * SIZE + b]));
    }
    printf("\n");
  }
}

void SDK_Apply(int32_t dst[SIZE][SIZE], int32_t src[SIZE][SIZE]) {
  for (int32_t a = 0; a < SIZE; a++) {
    for (int32_t b = 0; b < SIZE; b++) {
      dst[a * SIZE + b] &= src[a * SIZE + b];
    }
  }
}
