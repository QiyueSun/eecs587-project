// #include <iostream>
// #include <cstring>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <deque>
// #include <queue>
// #include <cmath>
// #include <fstream>
// #include <algorithm>
// #include <assert.h>
// #include <sys/time.h>
// #include <unordered_map>
// #include <unordered_set>
// #include <math.h>

// using namespace std;

// int N_2 = 0;
// int N = 0;

// bool is_conflict(vector<vector<int> >& sudoku) {
//     for (int i=0; i<N_2; i++) {
//         // for each row
//         vector<bool> exist(N_2, false);
//         for (int j=0; j<N_2; j++) {
//             if (sudoku[i][j] != 0) {
//                 if (exist[sudoku[i][j]-1]) {
//                     cout << "conflict at row " << i << endl;
//                     return true;
//                 }
//                 else
//                     exist[sudoku[i][j]-1] = true;
//             }
//         }
//         exist.clear();

//         // for each col
//         exist.resize(N_2, false);
//         for (int j=0; j<N_2; j++) {
//             if (sudoku[j][i] != 0) {
//                 if (exist[sudoku[j][i]-1]) {
//                     cout << "conflict at col " << i << endl;
//                     return true;
//                 }
//                 else
//                     exist[sudoku[j][i]-1] = true;
//             }
//         }
//         exist.clear();
//         // for each square
//         exist.resize(N_2, false);
//         int row_idx = i / N;
//         int col_idx = i % N;
//         for (int j=row_idx*N; j<(row_idx+1)*N; j++) {
//             for (int k=col_idx*N; k<(col_idx+1)*N; k++) {
//                 if (sudoku[j][k] != 0) {
//                     if (exist[sudoku[j][k]-1]) {
//                         cout << "conflict at box (" << row_idx << ", " << col_idx << ")" << endl;
//                         return true;
//                     }
//                     else
//                         exist[sudoku[j][k]-1] = true;
//                 }
//             }
//         }
//     }
//     return false;
// }

// bool helper(vector<vector<int> >& sudoku) {
//     // check conflict
//     if (is_conflict(sudoku)) {
//         return false;
//     }
//     // cout << "reach here" << endl;
//     // for (int i=0; i<N_2; i++) {
//     //     for (int j=0; j<sudoku[0].size(); j++) {
//     //         cout << sudoku[i][j] << " ";
//     //     }
//     //     cout << endl;
//     // }
//     // cout << endl;
//     for (int i=0; i<N_2; i++) {
//         for (int j=0; j<N_2; j++) {
//             if (sudoku[i][j] == 0) {
//                 // find all possible value
//                 unordered_set<int> possible_values;
//                 for (int k=0; k<N_2; k++) {
//                     possible_values.insert(k+1);
//                 }
//                 for (int k=0; k<N_2; k++) {
//                     // resolve conflict in row
//                     if (k != j && sudoku[i][k] != 0) {
//                         possible_values.erase(sudoku[i][k]);
//                     }
//                     // resolve conflict in column
//                     if (k != i && sudoku[k][j] != 0) {
//                         possible_values.erase(sudoku[k][j]);
//                     }
//                 }
//                 if (possible_values.empty())
//                     return false;
//                 auto it = possible_values.begin();
//                 for (;it != possible_values.end(); it++) {
//                     sudoku[i][j] = *it;
//                     bool result = helper(sudoku);
//                     if (result)
//                         return true;
//                 }
//                 sudoku[i][j] = 0;
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// int main(int argc, char* argv[]) {
//     string path_to_file = string(argv[1]);
//     ifstream file;
//     file.open(path_to_file);
//     vector<vector<int> > sudoku;
//     while (!file.eof()) {
//         string line;
//         getline(file, line);
//         vector<int> line_vector;
//         int prev = 0;
//         for (; prev<line.size(); prev++) {
//             if (line[prev] != ' ') {
//                 break;
//             }
//         }
//         int i=prev;
//         while (i < line.size()) {
//             for (; i<line.size(); i++) {
//                 if (line[i] == ' ') {
//                     break;
//                 }
//             }
//             int num = stoi(line.substr(prev, i));
//             line_vector.push_back(num);
//             while (line[i] == ' ') {
//                 i++;
//             }
//             prev = i;
//         }
//         sudoku.push_back(line_vector);
//     }
//     file.close();
    
//     N_2 = sudoku.size();
//     N = (int) sqrt(1.0 * N_2);
//     cout << "N = " << N << endl;

//     for (int i=0; i<N_2; i++) {
//         for (int j=0; j<sudoku[0].size(); j++) {
//             cout << sudoku[i][j] << " ";
//         }
//         cout << endl;
//     }
//     string result = helper(sudoku) ? "Solve the sudoku" : "Canot solve it";
//     cout << result << endl;
//     for (int i=0; i<N_2; i++) {
//         for (int j=0; j<sudoku[0].size(); j++) {
//             cout << sudoku[i][j] << " ";
//         }
//         cout << endl;
//     }

//     result = is_conflict(sudoku) ? "Find conflict in result" : "No conflict";
//     cout << result << endl;

    
//     // queue<pair<double, double> > waiting_queue;
//     // queue<pair<double, double> > task_queue;



//     // cout << "Total number of cores: " << max_threads << endl;
//     // cout << "Maximum value: " << M << endl;
//     // cout << "Time: " << (end_time - start_time) << endl;

//     return 0;
// }

#include <float.h> 
#include <stdlib.h> 
#include <bitset>
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
#include <mpi.h>
#include <stdio.h>
#include <string.h>
using namespace std; 

#define SIZE_MULTIPLIER 4
#define SIZE SIZE_MULTIPLIER * SIZE_MULTIPLIER

bool is_field_literal(int32_t field) {
    if (field == 0)
        return false;
    if (((field - 1) & field) == 0) 
        return true;
    return false;
}

int32_t translate_field(int32_t fld) {
    if (fld == 0) {
        return ~(fld & 0);
    }
    return 1 << (fld - 1);
}

int32_t to_pretty(int32_t field) {
  if (!is_field_literal(field)) {
    return 0;
  }
  if (field == 1) return 1;
    int32_t result = 0;
    if (((field + 1) & field) == 0) 
        return 0;
    while (field != 0) {
        field = field >> 1;
        result++;
    }
    return result;
}

void SDK_Pretty_Print(int32_t mtx[]) {
    for (int32_t a = 0; a < SIZE; a++) {
        for (int32_t b = 0; b < SIZE; b++) {
            printf("%2d ", to_pretty(mtx[a * SIZE + b]));
        }
        printf("\n");
    }
    cout << endl;
}

void SDK_More_Pretty_Print(int32_t mtx[]) {
    for (int32_t a = 0; a < SIZE; a++) {
        for (int32_t b = 0; b < SIZE; b++) {
            if (is_field_literal(mtx[a * SIZE + b])) {
                printf("%2d ", to_pretty(mtx[a * SIZE + b]));
            }
            else {
                int32_t field = mtx[a * SIZE + b];
                int count = 1;
                while (field != 0 && count != SIZE) {
                    if (field % 2 == 1) {
                        printf("%d,", count);
                    }
                    field = field >> 1;
                    count++;
                }
                printf(" ");
            }
        }
        printf("\n");
    }
}

void bit_print(int32_t kMATRIX[]) {
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            cout << std::bitset<16>(kMATRIX[i*SIZE + j]) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool is_conflict(int32_t sudoku[]) {
    for (int i=0; i<SIZE; i++) {
        // for each row
        vector<bool> exist(SIZE, false);
        int32_t nonexist = SIZE;
        int32_t nonliteral = 0;
        for (int j=0; j<SIZE; j++) {
            if (is_field_literal(sudoku[i * SIZE + j])) {
                if (exist[to_pretty(sudoku[i * SIZE + j])-1]) {
                    // cout << "conflict at row " << i << endl;
                    return true;
                }
                else {
                    exist[to_pretty(sudoku[i * SIZE + j])-1] = true;
                    nonexist--;
                }
            }
            else {
                nonliteral++;
            }
        }
        if (nonexist != nonliteral) {
            // cout << "conflict at row " << i << endl;
            return true;
        }
        exist.clear();

        // for each col
        exist.resize(SIZE, false);
        nonexist = SIZE;
        nonliteral = 0;
        for (int j=0; j<SIZE; j++) {
            if (is_field_literal(sudoku[j * SIZE + i])) {
                if (exist[to_pretty(sudoku[j * SIZE + i])-1]) {
                    // cout << "conflict at col " << i << endl;
                    return true;
                }
                else {
                    exist[to_pretty(sudoku[j * SIZE + i])-1] = true;
                    nonexist--;
                }
            }
            else {
                nonliteral++;
            }
        }
        if (nonexist != nonliteral) {
            // cout << "conflict at col " << i << endl;
            return true;
        }
        exist.clear();
        // for each square
        exist.resize(SIZE, false);
        nonexist = SIZE;
        nonliteral = 0;
        int row_idx = i / SIZE_MULTIPLIER;
        int col_idx = i % SIZE_MULTIPLIER;
        for (int j=row_idx*SIZE_MULTIPLIER; j<(row_idx+1)*SIZE_MULTIPLIER; j++) {
            for (int k=col_idx*SIZE_MULTIPLIER; k<(col_idx+1)*SIZE_MULTIPLIER; k++) {
                if (is_field_literal(sudoku[j * SIZE + k])) {
                    if (exist[to_pretty(sudoku[j * SIZE + k])-1]) {
                        // cout << "conflict at box (" << row_idx << ", " << col_idx << ")" << endl;
                        return true;
                    }
                    else {
                        exist[to_pretty(sudoku[j * SIZE + k])-1] = true;
                        nonexist--;
                    }
                }
                else {
                    nonliteral++;
                }
            }
        }
        if (nonexist != nonliteral) {
            // cout << "conflict at box (" << row_idx << ", " << col_idx << ")" << endl;
            return true;
        }
    }
    return false;
}

bool SDK_Check_Breakdown(int32_t mtx[]) {
    for (int32_t a = 0; a < SIZE; ++a) {
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
            if (!is_field_literal(field)) {
                return false;
            }
        }
    }
    return true;
}

void SDK_Import(string filepath, int32_t mtx[]) {
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

int32_t count_One(int32_t tmp) {
    int32_t counter = 0, i = 0;
    while (tmp != 0 && i < SIZE) {
        if (tmp % 2 == 1)
            counter++;
        tmp = tmp >> 1;
        i++;
    }
    return counter;
}

bool SDK_Mark_Vertical_Availables(int32_t mtx[], bool& assert_fail, int32_t start_col, int32_t end_col) {
    bool change = false;
    for (int32_t a = start_col; a < end_col; ++a) {
        //  Find used numbers
        int32_t num_of_nonliteral = 0, result = 0;
        for (int32_t b = 0; b < SIZE; ++b) {
            if (is_field_literal(mtx[b * SIZE + a]))
                result |= mtx[b * SIZE + a];
            else
                num_of_nonliteral++;
        }

        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ ((1 << SIZE) - 1);
        assert(count_One(unused_numbers) == num_of_nonliteral);

        for (int32_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[b * SIZE + a])) {
                int32_t old = mtx[b * SIZE + a];
                mtx[b * SIZE + a] &= unused_numbers;
                change |= old != mtx[b * SIZE + a];
                if (mtx[b * SIZE + a] == 0) {
                    assert_fail = true;
                    return true;
                }
                // assert(mtx[b * SIZE + a] != 0);
            }
        }
    }
    return change;
}

bool SDK_Mark_Horizontal_Availables(int32_t mtx[], bool& assert_fail, int32_t start_row, int32_t end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; ++a) {
        int32_t result = 0, num_of_nonliteral = 0;
        for (int32_t b = 0; b < SIZE; ++b) {
            if (is_field_literal(mtx[a * SIZE + b]))
                result |= mtx[a * SIZE + b];
            else
                num_of_nonliteral++;
        }
        
        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ ((1 << SIZE) - 1);
        assert(count_One(unused_numbers) == num_of_nonliteral);

        for (int32_t b = 0; b < SIZE; ++b) {
            if (!is_field_literal(mtx[a * SIZE + b])) {
                int32_t old = mtx[a * SIZE + b];
                mtx[a * SIZE + b] &= unused_numbers;
                change |= old != mtx[a * SIZE + b];
                if (mtx[a * SIZE + b] == 0) {
                    assert_fail = true;
                    return true;
                }
                // assert(mtx[a * SIZE + b] != 0);
            }
        }
    }
    return change;
}

bool SDK_Mark_Subbox_Availables(int32_t mtx[], bool& assert_fail, int32_t start_box_idx, int32_t end_box_idx) {
    bool change = false;
    for (int32_t i = start_box_idx; i < end_box_idx; i++) {
        int32_t a = i / SIZE_MULTIPLIER;
        int32_t b = i % SIZE_MULTIPLIER;
        //  Find used numbers
        int32_t result = 0, num_of_nonliteral = 0;
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (is_field_literal(field))
                    result |= field;
                else
                    num_of_nonliteral++;
            }
        }

        //  Insert unused numbers to empty fields
        int32_t unused_numbers = result ^ ((1 << SIZE) - 1);
        assert(count_One(unused_numbers) == num_of_nonliteral);

        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                if (!is_field_literal(mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d])) {
                    int32_t old = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                    mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] &= unused_numbers;
                    change |= old != mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                    if (mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] == 0) {
                        assert_fail = true;
                        return true;
                    }
                    // assert(mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] != 0);
                }
            }
        }
    }
    
    return change;
}

bool SDK_Mark_Vertical_Availables_Long_Ranger(int32_t mtx[], int32_t start_col, int32_t end_col) {
    bool change = false;
    for (int32_t a = start_col; a < end_col; ++a) {
        int32_t result = 0;
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[b * SIZE + a];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1)
                        set_bits[count].push_back(b);
                    count++;
                    field = field >> 1;
                }
            }
        }
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 1) {
                int32_t b = set_bits[i][0];
                if (!is_field_literal(mtx[b * SIZE + a])) {
                    assert((mtx[b * SIZE + a] >> i) % 2 == 1);
                    int32_t old = mtx[b * SIZE + a];
                    mtx[b * SIZE + a] = 1 << i;
                    assert(old != mtx[b * SIZE + a]);
                    change = true;
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Horizontal_Availables_Long_Ranger(int32_t mtx[], int start_row, int end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; ++a) {
        int32_t result = 0;
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1) {
                        set_bits[count].push_back(b);
                    }
                    count++;
                    field = field >> 1;
                }
            }
        }
        // print out set_bits
        // cout << "print out set_bits" << endl;
        // for (int i=0; i<set_bits.size(); i++) {
        //     for (int j=0; j<set_bits[i].size(); j++) {
        //         cout << set_bits[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 1) {
                int32_t b = set_bits[i][0];
                if (!is_field_literal(mtx[a * SIZE + b])) {
                    // assert(!is_field_literal(mtx[a * SIZE + b]) && (mtx[a * SIZE + b] >> i) % 2 == 1);
                    if ((mtx[a * SIZE + b] >> i) % 2 != 1) {
                        cout << "Fail assert at ( " << a << " , " << b << " )" << endl;
                        SDK_Pretty_Print(mtx);
                    }
                    assert((mtx[a * SIZE + b] >> i) % 2 == 1);
                    int32_t old = mtx[a * SIZE + b];
                    mtx[a * SIZE + b] = 1 << i;
                    assert(old != mtx[a * SIZE + b]);
                    change = true;
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Subbox_Availables_Long_Ranger(int32_t mtx[], int start_box_idx, int end_box_idx) {
    bool change = false;
    for (int32_t i = start_box_idx; i < end_box_idx; i++) {
        int32_t a = i / SIZE_MULTIPLIER;
        int32_t b = i % SIZE_MULTIPLIER;
        int32_t result = 0;
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    int count = 0;
                    while (field != 0 && count != SIZE) {
                        // check if the last bit is 1
                        if (field % 2 == 1) {
                            set_bits[count].push_back(c * SIZE_MULTIPLIER + d);
                        }
                        count++;
                        field = field >> 1;
                    }
                }
            }
        }
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 1) {
                int32_t c = set_bits[i][0] / SIZE_MULTIPLIER;
                int32_t d = set_bits[i][0] % SIZE_MULTIPLIER;
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    assert((field >> i) % 2 == 1);
                    int32_t old = field;
                    mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d] = 1 << i;
                    assert(old != mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d]);
                    change = true;
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Vertical_Availables_Twins(int32_t mtx[], int start_col, int end_col) {
    // cout << "Vertical Twin" << endl;
    bool change = false;
    for (int32_t a = start_col; a < end_col; a++) {
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[b * SIZE + a];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1) {
                        set_bits[count].push_back(b);
                    }
                    count++;
                    field = field >> 1;
                }
            }
        }
        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 2) {
                possible_twins_idx.push_back(i);
            }
        }
        // cout << "possible_twins_idx size: " << possible_twins_idx.size() << endl;
        if (possible_twins_idx.empty()) {
            continue;
        }
        for (int i=0; i<possible_twins_idx.size()-1; i++) {
            for (int j=i+1; j<possible_twins_idx.size(); j++) {
                if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                    set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1]) {
                    // remove other values
                    int32_t old_1 = mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a];
                    int32_t old_2 = mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a];
                    if ((old_1 >> possible_twins_idx[i]) % 2 == 1 &&
                        (old_1 >> possible_twins_idx[j]) % 2 == 1 &&
                        (old_2 >> possible_twins_idx[i]) % 2 == 1 &&
                        (old_2 >> possible_twins_idx[j]) % 2 == 1) {
                        mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        change = (old_1 != mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a]) ||
                                (old_2 != mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a]);
                        break;
                    }
                }
            }
        }
    }
    // cout << "SDK_Mark_Vertical_Availables_Twins return" << endl;
    return change;
}

bool SDK_Mark_Horizontal_Availables_Twins(int32_t mtx[], int start_row, int end_row) {
    // cout << "Horizontal Twin" << endl;
    bool change = false;
    for (int32_t a = start_row; a < end_row; a++) {
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1) {
                        set_bits[count].push_back(b);
                    }
                    count++;
                    field = field >> 1;
                }
            }
        }
        // print out set_bits
        // cout << "print out set_bits" << endl;
        // for (int i=0; i<set_bits.size(); i++) {
        //     for (int j=0; j<set_bits[i].size(); j++) {
        //         cout << set_bits[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 2) {
                possible_twins_idx.push_back(i);
            }
        }
        if (possible_twins_idx.empty()) {
          continue;
        }
        for (int i=0; i<possible_twins_idx.size()-1; i++) {
            for (int j=i+1; j<possible_twins_idx.size(); j++) {
                if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                    set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1]) {
                    // remove other values
                    int32_t old_1 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]];
                    int32_t old_2 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]];
                    if ((old_1 >> possible_twins_idx[i]) % 2 == 1 &&
                        (old_1 >> possible_twins_idx[j]) % 2 == 1 &&
                        (old_2 >> possible_twins_idx[i]) % 2 == 1 &&
                        (old_2 >> possible_twins_idx[j]) % 2 == 1) {
                        mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        change = (old_1 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]]) ||
                                (old_2 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]]);
                        break;
                    }
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Subbox_Availables_Twins(int32_t mtx[], int start_box_idx, int end_box_idx) {
    // cout << "Subbox Twin" << endl;
    bool change = false;
    for (int32_t box = start_box_idx; box < end_box_idx; box++) {
        int32_t a = box / SIZE_MULTIPLIER;
        int32_t b = box % SIZE_MULTIPLIER;
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    int count = 0;
                    while (field != 0 && count != SIZE) {
                        // check if the last bit is 1
                        if (field % 2 == 1) {
                            set_bits[count].push_back(c * SIZE_MULTIPLIER + d);
                        }
                        count++;
                        field = field >> 1;
                    }
                }
            }
        }

        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 2) {
                possible_twins_idx.push_back(i);
            }
        }
        if (possible_twins_idx.empty()) {
          continue;
        }
        // cout << "possible_twins_idx size = " << possible_twins_idx.size() << endl;
        for (int i=0; i<possible_twins_idx.size()-1; i++) {
            for (int j=i+1; j<possible_twins_idx.size(); j++) {
                if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                    set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1]) {
                    // remove other values
                    int32_t c1 = set_bits[possible_twins_idx[i]][0] / SIZE_MULTIPLIER;
                    int32_t d1 = set_bits[possible_twins_idx[i]][0] % SIZE_MULTIPLIER;
                    int32_t c2 = set_bits[possible_twins_idx[i]][1] / SIZE_MULTIPLIER;
                    int32_t d2 = set_bits[possible_twins_idx[i]][1] % SIZE_MULTIPLIER;
                    int32_t old_1 = mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]; 
                    int32_t old_2 = mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2];
                    if ((old_1 >> possible_twins_idx[i]) % 2 == 1 &&
                        (old_1 >> possible_twins_idx[j]) % 2 == 1 &&
                        (old_2 >> possible_twins_idx[i]) % 2 == 1 &&
                        (old_2 >> possible_twins_idx[j]) % 2 == 1) {
                        mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        // mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        // mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]);
                        change = (old_1 != mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]) ||
                                (old_2 != mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2]);
                        break;
                    }
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Vertical_Availables_Triplets(int32_t mtx[], int start_col, int end_col) {
    bool change = false;
    for (int32_t a = start_col; a < end_col; a++) {
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[b * SIZE + a];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1) {
                        set_bits[count].push_back(b);
                    }
                    count++;
                    field = field >> 1;
                }
            }
        }
        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 3) {
                possible_twins_idx.push_back(i);
            }
        }
        if (possible_twins_idx.size() < 3) {
            continue;
        }
        for (int i=0; i<possible_twins_idx.size()-2; i++) {
            for (int j=i+1; j<possible_twins_idx.size()-1; j++) {
                for (int k=j+1; k<possible_twins_idx.size(); k++) {
                    if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                        set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[k]][0] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[k]][1] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[j]][2] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[k]][2]) {
                        // remove other values
                        int32_t old_1 = mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a];
                        int32_t old_2 = mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a];
                        int32_t old_3 = mtx[set_bits[possible_twins_idx[i]][2] * SIZE + a];
                        if (
                            (old_1 >> possible_twins_idx[i]) % 2 == 1 && (old_1 >> possible_twins_idx[j]) % 2 == 1 && (old_1 >> possible_twins_idx[k]) % 2 == 1 &&
                            (old_2 >> possible_twins_idx[i]) % 2 == 1 && (old_2 >> possible_twins_idx[j]) % 2 == 1 && (old_2 >> possible_twins_idx[k]) % 2 == 1 &&
                            (old_3 >> possible_twins_idx[i]) % 2 == 1 && (old_3 >> possible_twins_idx[j]) % 2 == 1 && (old_3 >> possible_twins_idx[k]) % 2 == 1
                        ) {
                            mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            mtx[set_bits[possible_twins_idx[i]][2] * SIZE + a] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            change = change ||
                                    (old_1 != mtx[set_bits[possible_twins_idx[i]][0] * SIZE + a]) ||
                                    (old_2 != mtx[set_bits[possible_twins_idx[i]][1] * SIZE + a]) ||
                                    (old_3 != mtx[set_bits[possible_twins_idx[i]][2] * SIZE + a]);
                            break;
                        }
                    }
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Horizontal_Availables_Triplets(int32_t mtx[], int start_row, int end_row) {
    bool change = false;
    for (int32_t a = start_row; a < end_row; a++) {
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t b = 0; b < SIZE; ++b) {
            int32_t field = mtx[a * SIZE + b];
            if (!is_field_literal(field)) {
                int count = 0;
                while (field != 0 && count != SIZE) {
                    // check if the last bit is 1
                    if (field % 2 == 1) {
                        set_bits[count].push_back(b);
                    }
                    count++;
                    field = field >> 1;
                }
            }
        }
        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 3) {
                possible_twins_idx.push_back(i);
            }
        }
        if (possible_twins_idx.size() < 3) {
          continue;
        }
        for (int i=0; i<possible_twins_idx.size()-2; i++) {
            for (int j=i+1; j<possible_twins_idx.size()-1; j++) {
                for (int k=j+1; k<possible_twins_idx.size(); k++) {
                    if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                        set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[k]][0] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[k]][1] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[j]][2] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[k]][2]) {
                        // remove other values
                        int32_t old_1 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]];
                        int32_t old_2 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]];
                        int32_t old_3 = mtx[a * SIZE + set_bits[possible_twins_idx[i]][2]];
                        if (
                            (old_1 >> possible_twins_idx[i]) % 2 == 1 && (old_1 >> possible_twins_idx[j]) % 2 == 1 && (old_1 >> possible_twins_idx[k]) % 2 == 1 &&
                            (old_2 >> possible_twins_idx[i]) % 2 == 1 && (old_2 >> possible_twins_idx[j]) % 2 == 1 && (old_2 >> possible_twins_idx[k]) % 2 == 1 &&
                            (old_3 >> possible_twins_idx[i]) % 2 == 1 && (old_3 >> possible_twins_idx[j]) % 2 == 1 && (old_3 >> possible_twins_idx[k]) % 2 == 1
                        ) {
                            mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            mtx[a * SIZE + set_bits[possible_twins_idx[i]][2]] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            change = change || 
                                    (old_1 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][0]]) ||
                                    (old_2 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][1]]) ||
                                    (old_3 != mtx[a * SIZE + set_bits[possible_twins_idx[i]][2]]);
                            break;
                        }
                    }
                }
            }
        }
    }
    return change;
}

bool SDK_Mark_Subbox_Availables_Triplets(int32_t mtx[], int start_box_idx, int end_box_idx) {
    bool change = false;
    for (int32_t box = start_box_idx; box < end_box_idx; box++) {
        int32_t a = box / SIZE_MULTIPLIER;
        int32_t b = box % SIZE_MULTIPLIER;
        std::vector<std::vector<int> > set_bits(SIZE, std::vector<int>());
        for (int32_t c = 0; c < SIZE_MULTIPLIER; ++c) {
            for (int32_t d = 0; d < SIZE_MULTIPLIER; ++d) {
                int32_t field = mtx[((a * SIZE_MULTIPLIER) + c) * SIZE + (b * SIZE_MULTIPLIER) + d];
                if (!is_field_literal(field)) {
                    int count = 0;
                    while (field != 0 && count != SIZE) {
                        // check if the last bit is 1
                        if (field % 2 == 1) {
                            set_bits[count].push_back(c * SIZE_MULTIPLIER + d);
                        }
                        count++;
                        field = field >> 1;
                    }
                }
            }
        }

        std::vector<int> possible_twins_idx;
        for (int i=0; i<SIZE; i++) {
            if (set_bits[i].size() == 3) {
                possible_twins_idx.push_back(i);
            }
        }
        if (possible_twins_idx.size() < 3) {
          continue;
        }
        for (int i=0; i<possible_twins_idx.size()-2; i++) {
            for (int j=i+1; j<possible_twins_idx.size()-1; j++) {
                for (int k=j+1; k<possible_twins_idx.size(); k++) {
                    if (set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[j]][0] &&
                        set_bits[possible_twins_idx[i]][0] == set_bits[possible_twins_idx[k]][0] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[j]][1] &&
                        set_bits[possible_twins_idx[i]][1] == set_bits[possible_twins_idx[k]][1] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[j]][2] &&
                        set_bits[possible_twins_idx[i]][2] == set_bits[possible_twins_idx[k]][2]) {
                        // remove other values
                        int32_t c1 = set_bits[possible_twins_idx[i]][0] / SIZE_MULTIPLIER;
                        int32_t d1 = set_bits[possible_twins_idx[i]][0] % SIZE_MULTIPLIER;
                        int32_t c2 = set_bits[possible_twins_idx[i]][1] / SIZE_MULTIPLIER;
                        int32_t d2 = set_bits[possible_twins_idx[i]][1] % SIZE_MULTIPLIER;
                        int32_t c3 = set_bits[possible_twins_idx[i]][2] / SIZE_MULTIPLIER;
                        int32_t d3 = set_bits[possible_twins_idx[i]][2] % SIZE_MULTIPLIER;
                        int32_t old_1 = mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]; 
                        int32_t old_2 = mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2];
                        int32_t old_3 = mtx[((a * SIZE_MULTIPLIER) + c3) * SIZE + (b * SIZE_MULTIPLIER) + d3];
                        if (
                            (old_1 >> possible_twins_idx[i]) % 2 == 1 && (old_1 >> possible_twins_idx[j]) % 2 == 1 && (old_1 >> possible_twins_idx[k]) % 2 == 1 &&
                            (old_2 >> possible_twins_idx[i]) % 2 == 1 && (old_2 >> possible_twins_idx[j]) % 2 == 1 && (old_2 >> possible_twins_idx[k]) % 2 == 1 &&
                            (old_3 >> possible_twins_idx[i]) % 2 == 1 && (old_3 >> possible_twins_idx[j]) % 2 == 1 && (old_3 >> possible_twins_idx[k]) % 2 == 1
                        ) {
                            mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            mtx[((a * SIZE_MULTIPLIER) + c3) * SIZE + (b * SIZE_MULTIPLIER) + d3] = (1 << possible_twins_idx[i]) + (1 << possible_twins_idx[j]) + (1 << possible_twins_idx[k]);
                            change = change ||
                                    (old_1 != mtx[((a * SIZE_MULTIPLIER) + c1) * SIZE + (b * SIZE_MULTIPLIER) + d1]) ||
                                    (old_2 != mtx[((a * SIZE_MULTIPLIER) + c2) * SIZE + (b * SIZE_MULTIPLIER) + d2]) ||
                                    (old_3 != mtx[((a * SIZE_MULTIPLIER) + c3) * SIZE + (b * SIZE_MULTIPLIER) + d3]);
                            break;
                        }
                    }
                }
            }
        }
    }
    return change;
}

int apply_humanistic(int32_t kMATRIX[]) {
    while (!is_conflict(kMATRIX)) {
        bool assert_fail = false;
        bool change = SDK_Mark_Vertical_Availables(kMATRIX, assert_fail, 0, SIZE);
        if (assert_fail) break;
        change |= SDK_Mark_Horizontal_Availables(kMATRIX, assert_fail, 0, SIZE);
        if (assert_fail) break;
        change |= SDK_Mark_Subbox_Availables(kMATRIX, assert_fail, 0, SIZE);
        if (assert_fail) break;
        if (change) continue;
        change = SDK_Mark_Vertical_Availables_Long_Ranger(kMATRIX, 0, SIZE);
        change |= SDK_Mark_Horizontal_Availables_Long_Ranger(kMATRIX, 0, SIZE);
        change |= SDK_Mark_Subbox_Availables_Long_Ranger(kMATRIX, 0, SIZE);
        if (change) continue;
        change = SDK_Mark_Vertical_Availables_Twins(kMATRIX, 0, SIZE);
        change |= SDK_Mark_Horizontal_Availables_Twins(kMATRIX, 0, SIZE);
        change |= SDK_Mark_Subbox_Availables_Twins(kMATRIX, 0, SIZE);
        if (change) continue;
        else break;
    }
    if (is_conflict(kMATRIX)) {
        return 2;
    }
    else if (SDK_Check_Breakdown(kMATRIX)) {
        return 0;
    }
    return 1;
}

bool brute_force(int32_t mtx[]) {
    if (is_conflict(mtx))
        return false;
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (!is_field_literal(mtx[i * SIZE + j])) {
                unordered_set<int32_t> possible_values;
                int k = 1;
                while (k < (1 << SIZE)) {
                    possible_values.insert(k);
                    k = k << 1;
                }
                for (int k=0; k<SIZE; k++) {
                    // resolve conflict in row
                    if (k != j && is_field_literal(mtx[i * SIZE + k])) {
                        possible_values.erase(mtx[i * SIZE + k]);
                    }
                    // resolve conflict in column
                    if (k != i && is_field_literal(mtx[k * SIZE + j])) {
                        possible_values.erase(mtx[k * SIZE + j]);
                    }
                    int32_t c = (i / SIZE_MULTIPLIER) * SIZE_MULTIPLIER;
                    int32_t d = (j / SIZE_MULTIPLIER) * SIZE_MULTIPLIER;
                    int32_t idx = (c + k / SIZE_MULTIPLIER) * SIZE + d + k % SIZE_MULTIPLIER;
                    if (idx != (i * SIZE + j) && is_field_literal(mtx[idx])) {
                        possible_values.erase(mtx[idx]);
                    }
                }
                if (possible_values.empty())
                    return false;
                auto it = possible_values.begin();
                int32_t old = mtx[i * SIZE + j];
                for (; it != possible_values.end(); it++) {
                    mtx[i * SIZE + j] = *it;
                    bool result = brute_force(mtx);
                    if (result)
                        return true;
                }
                mtx[i * SIZE + j] = old;
                return false;
            }
        }
    }
    return true;
}

bool SDK_Apply(int32_t dst[], int32_t src[]) {
    bool change = false;
    for (int32_t a = 0; a < SIZE*SIZE; a++) {
        int32_t old = dst[a];
        dst[a] &= src[a];
        if (dst[a] != old) change = true;
    }
    return change;
}

void SDK_Copy(int32_t dst[], int32_t src[]) {
    for (int32_t a = 0; a < SIZE*SIZE; a++) {
        dst[a] = src[a];
    }
}

int main(int argc, char *argv[]) {
    int32_t kMATRIX[SIZE*SIZE];
    int32_t* tmp = new int32_t[SIZE*SIZE];
    SDK_Import(string(argv[1]), kMATRIX);
    // "EECS 587/project/testcases/9x9_easy2.txt"
    SDK_Pretty_Print(kMATRIX);
    memcpy(tmp, kMATRIX, SIZE*SIZE*sizeof(int32_t));
    vector<int32_t*> stack(1, tmp);
    bool solved = false;
    double start_time = MPI_Wtime();
    while (!stack.empty()) {
        tmp = stack.back(); stack.pop_back();
        memcpy(kMATRIX, tmp, SIZE*SIZE*sizeof(int32_t));
        delete []tmp; 
        // cout << "stack size = " << stack.size() << endl;
        bool assert_fail = false;
        while (!is_conflict(kMATRIX)) {
            int32_t tmp1[SIZE*SIZE]; SDK_Copy(tmp1, kMATRIX);
            int32_t tmp2[SIZE*SIZE]; SDK_Copy(tmp2, kMATRIX);
            bool change = SDK_Mark_Vertical_Availables(kMATRIX, assert_fail, 0, SIZE);
            // cout << "SDK_Mark_Vertical_Availables" << endl;
            if (assert_fail) break;
            SDK_Mark_Horizontal_Availables(tmp1, assert_fail, 0, SIZE);
            if (assert_fail) break;
            SDK_Mark_Subbox_Availables(tmp2, assert_fail, 0, SIZE);
            change |= SDK_Apply(kMATRIX, tmp1) || SDK_Apply(kMATRIX, tmp2);
            if (change) continue;
            SDK_Copy(tmp1, kMATRIX); SDK_Copy(tmp2, kMATRIX);
            change = SDK_Mark_Vertical_Availables_Long_Ranger(kMATRIX, 0, SIZE);
            // cout << "SDK_Mark_Vertical_Availables_Long_Ranger" << endl;
            SDK_Mark_Horizontal_Availables_Long_Ranger(tmp1, 0, SIZE);
            SDK_Mark_Subbox_Availables_Long_Ranger(tmp2, 0, SIZE);
            change |= SDK_Apply(kMATRIX, tmp1) || SDK_Apply(kMATRIX, tmp2);
            if (change) continue;
            SDK_Copy(tmp1, kMATRIX); SDK_Copy(tmp2, kMATRIX);
            change = SDK_Mark_Vertical_Availables_Twins(kMATRIX, 0, SIZE);
            // cout << "SDK_Mark_Vertical_Availables_Twins" << endl;
            SDK_Mark_Horizontal_Availables_Twins(kMATRIX, 0, SIZE);
            SDK_Mark_Subbox_Availables_Twins(kMATRIX, 0, SIZE);
            change |= SDK_Apply(kMATRIX, tmp1) || SDK_Apply(kMATRIX, tmp2);
            if (change) continue;
            SDK_Copy(tmp1, kMATRIX); SDK_Copy(tmp2, kMATRIX);
            change = SDK_Mark_Vertical_Availables_Triplets(kMATRIX, 0, SIZE);
            // cout << "SDK_Mark_Vertical_Availables_Triplets" << endl;
            SDK_Mark_Horizontal_Availables_Triplets(kMATRIX, 0, SIZE);
            SDK_Mark_Subbox_Availables_Triplets(kMATRIX, 0, SIZE);
            change |= SDK_Apply(kMATRIX, tmp1) || SDK_Apply(kMATRIX, tmp2);
            if (change) continue;
            int32_t start_idx = 0;
            while (start_idx < SIZE*SIZE && is_field_literal(kMATRIX[start_idx]))
                start_idx++;
            if (start_idx ==  SIZE*SIZE)
                break;
            SDK_Permutations(kMATRIX, stack, start_idx, start_idx + 5);
            cout << "new stack size = " << stack.size() << endl;
            if (stack.size() > 4000) {
                while (!stack.empty()) {
                    int32_t* tmp = stack.back(); stack.pop_back();
                    memcpy(kMATRIX, tmp, SIZE*SIZE);
                    delete[] tmp;
                    int result = apply_humanistic(kMATRIX);
                    solved = false;
                    if (result == 1) {
                        solved = brute_force(kMATRIX);
                    }
                    else if (result == 0) {
                        solved = true;
                    }
                    if (solved) break;
                }
            }
            break;
        }
        if (solved) {
            assert(SDK_Check_Breakdown(kMATRIX) && !is_conflict(kMATRIX));
        }
        if (SDK_Check_Breakdown(kMATRIX) && !is_conflict(kMATRIX)) {
            break;
        }
    }
    double duration = MPI_Wtime() - start_time;
    cout << "p:" << 1 << "\nRunning time:" << duration << endl;
    SDK_More_Pretty_Print(kMATRIX);
    return 0;
}
