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

bool helper(vector<vector<int> >& sudoku) {
    // check conflict
    if (is_conflict(sudoku)) {
        return false;
    }
    // cout << "reach here" << endl;
    // for (int i=0; i<N_2; i++) {
    //     for (int j=0; j<sudoku[0].size(); j++) {
    //         cout << sudoku[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    for (int i=0; i<N_2; i++) {
        for (int j=0; j<N_2; j++) {
            if (sudoku[i][j] == 0) {
                // find all possible value
                unordered_set<int> possible_values;
                for (int k=0; k<N_2; k++) {
                    possible_values.insert(k+1);
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
                    bool result = helper(sudoku);
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

int main(int argc, char* argv[]) {
    string path_to_file = string(argv[1]);
    ifstream file;
    file.open(path_to_file);
    vector<vector<int> > sudoku;
    while (!file.eof()) {
        string line;
        getline(file, line);
        vector<int> line_vector;
        int prev = 0;
        int i=prev;
        while (i < line.size()) {
            for (; i<line.size(); i++) {
                if (line[i] == ' ') {
                    break;
                }
            }
            int num = stoi(line.substr(prev, i));
            line_vector.push_back(num);
            i++;
            prev = i;
        }
        sudoku.push_back(line_vector);
    }
    file.close();
    
    N_2 = sudoku.size();
    N = (int) sqrt(1.0 * N_2);
    cout << "N = " << N << endl;

    for (int i=0; i<N_2; i++) {
        for (int j=0; j<sudoku[0].size(); j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
    string result = helper(sudoku) ? "true" : "false";
    cout << result << endl;
    for (int i=0; i<N_2; i++) {
        for (int j=0; j<sudoku[0].size(); j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }

    result = is_conflict(sudoku) ? "true" : "false";
    cout << result << endl;

    
    // queue<pair<double, double> > waiting_queue;
    // queue<pair<double, double> > task_queue;



    // cout << "Total number of cores: " << max_threads << endl;
    // cout << "Maximum value: " << M << endl;
    // cout << "Time: " << (end_time - start_time) << endl;

    return 0;
}
