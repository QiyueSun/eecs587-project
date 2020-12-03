#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <sys/time.h>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <assert.h>

using namespace std;


int N_2 = 0;
int N = 0;

bool is_conflict(vector<vector<int> >& sudoku) {
    for (int i=0; i<N_2; i++) {
        // for each row
        vector<bool> exist(N_2, false);
        for (int j=0; j<N_2; j++) {
            if (sudoku[i][j] != 0) {
                if (exist[sudoku[i][j]-1])
                    return true;
                else
                    exist[sudoku[i][j]-1] = true;
            }
        }
        exist.clear();

        // for each col
        exist.resize(N_2, false);
        for (int j=0; j<N_2; j++) {
            if (sudoku[j][i] != 0) {
                if (exist[sudoku[j][i]-1])
                    return true;
                else
                    exist[sudoku[j][i]-1] = true;
            }
        }
        exist.clear();

        // for each square
        exist.resize(N_2, false);
        int row_idx = i / N;
        int col_idx = i % N;
        for (int j=row_idx*N; j<(row_idx+1)*N; j++) {
            for (int k=col_idx*N; k<(col_idx+1)*N; k++) {
                if (sudoku[j][k] != 0) {
                    if (exist[sudoku[j][k]-1])
                        return true;
                    else
                        exist[sudoku[j][k]-1] = true;
                }
            }
        }
    }
    return false;
}

bool generate_sudoku(vector<vector<int> >& sudoku) {
    // check conflict
    if (is_conflict(sudoku)) {
        return false;
    }
    for (int i=0; i<N_2; i++) {
        for (int j=0; j<N_2; j++) {
            if (sudoku[i][j] == 0) {
                // find all possible value
                unordered_set<int> possible_values;
                int rand_num = rand() % N_2 + 1;
                for (int k=rand_num; k<rand_num+N_2; k++) {
                    possible_values.insert(k % N_2 + 1);
                }
                for (int k=0; k<N_2; k++) {
                    // resolve conflict in row
                    if (k != j && sudoku[i][k] != 0) {
                        possible_values.erase(sudoku[i][k]);
                    }
                    // resolve conflict in column
                    if (k != i && sudoku[k][j] != 0) {
                        possible_values.erase(sudoku[k][j]);
                    }
                }
                if (possible_values.empty())
                    return false;
                auto it = possible_values.begin();
                for (;it != possible_values.end(); it++) {
                    sudoku[i][j] = *it;
                    bool result = generate_sudoku(sudoku);
                    if (result)
                        return true;
                }
                sudoku[i][j] = 0;
                return false;
            }
        }
    }
    return true;
}



int main(int argc, char *argv[]) {
    // size = N^2, where N = 3, 4, 5, ...
    // ./generator <size> <output_dir>
    int size = atoi(argv[1]);
    N_2 = size;
    N = (int) sqrt(size);
    string output_dir = string(argv[2]);
    vector<float> level({0.3, 0.4, 0.5, 0.6, 0.7});

    int counter = 0;
    while (counter < 5) {
        for (float l : level) {
            vector<vector<int> > sudoku(size, vector<int>(size, 0));
            generate_sudoku(sudoku);

            int k = (int) (l * size * size);
            cout << "hidden: " << k << endl;
            for (int i=0; i<k; i++) {
                int rand_num = rand() % (size * size);
                while (sudoku[rand_num / size][rand_num % size] == 0) {
                    rand_num = rand() % (size * size);
                }
                sudoku[rand_num / size][rand_num % size] = 0;
            }
            cout << endl;
            for (int i=0; i<size; i++) {
                for (int j=0; j<size; j++) {
                    cout << sudoku[i][j] << " ";
                }
                cout << endl;
            }
            cout << "##################" << endl;
            counter++;
            ofstream myfile;
            
            to_string(size) + "x" + to_string(size) + "_eas" + to_string(k);
            myfile.open ("example.txt");
            myfile << "Writing this to a file.\n";
        }
    }

    
    return 0;
}