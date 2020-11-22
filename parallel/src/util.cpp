#include "util.h"
#include "defs.h"
#include <vector>
#include <string>
#include <fstream>

#include "field.h"

using namespace std;

void SDK_Import(string filepath, vector<vector<int64_t>>& mtx) {
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
            mtx[row_idx][col_idx] = translate_field(num);
            i++; prev = i; col_idx++;
        }
        row_idx++;
    }
    file.close();
}

void SDK_Copy(vector<vector<int64_t>> src, vector<vector<int64_t>> dst) {
  for (int64_t a = 0; a < SIZE; a++) {
    for (int64_t b = 0; b < SIZE; b++) {
      dst[a][b] = src[a][b];
    }
  }
}

void SDK_Print(vector<vector<int64_t>> mtx) {
  for (int64_t a = 0; a < SIZE; a++) {
    for (int64_t b = 0; b < SIZE; b++) {
      printf("%d ", mtx[a][b]);
    }
    printf("\n");
  }
}

void SDK_Pretty_Print(vector<vector<int64_t>> mtx) {
  for (int64_t a = 0; a < SIZE; a++) {
    for (int64_t b = 0; b < SIZE; b++) {
      printf("%d ", to_pretty(mtx[a][b]));
    }
    printf("\n");
  }
}

void SDK_Apply(vector<vector<int64_t>> dst, int64_t src[]) {
  for (int64_t a = 0; a < SIZE; a++) {
    for (int64_t b = 0; b < SIZE; b++) {
      dst[a][b] &= src[a*SIZE + b];
    }
  }
}
