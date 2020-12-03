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

#include "defs.h"
#include "field.h"
#include "util.h"
#include "vertical.h"
#include "horizontal.h"
#include "subbox.h"
#include "breakdown.h"

using namespace std;

int main(int argc, char *argv[]) {
    int32_t kMATRIX[SIZE*SIZE];
    SDK_Import(string(argv[1]), kMATRIX);

    MPI_Init(&argc, &argv);

    int comm_size;
    int comm_rank;
    bool is_master = false;
    double time_start;

    if (MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank) != MPI_SUCCESS) {
        fprintf(stderr, "%s\n", "error: cannot get rank");
    }

    if (MPI_Comm_size(MPI_COMM_WORLD, &comm_size) != MPI_SUCCESS) {
        fprintf(stderr, "%s\n", "error: cannot get size");
    }

    if (comm_rank == 0) {
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                cout << kMATRIX[i*SIZE+j] << " ";
            }
            cout << endl;
        }
        is_master = true;
        time_start = MPI_Wtime();
    }
    int count = 0;
    bool change = true;
    bool assert_fail = false;
    bool finish = false;
    bool conflict = false;
    int32_t* tmp = new int32_t[SIZE*SIZE];
    vector<int32_t*> stack;
    if (comm_rank == 0) {
        memcpy(tmp, kMATRIX, SIZE*SIZE*sizeof(int32_t));
        stack.push_back(tmp);
    }

    while (true) {
        while (!conflict) {
            // elimination
            if (comm_rank == 0) {
                change = SDK_Mark_Vertical_Availables(kMATRIX, assert_fail, 0, SIZE);
                int32_t tmp_arr1[SIZE*SIZE];
                int32_t tmp_arr2[SIZE*SIZE];
                bool assert_fail1 = false;
                bool assert_fail2 = false;
                MPI_Recv(tmp_arr1, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                MPI_Recv(&assert_fail1, 1, MPI_C_BOOL, 1, 0, MPI_COMM_WORLD, NULL);
                MPI_Recv(tmp_arr2, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                MPI_Recv(&assert_fail2, 1, MPI_C_BOOL, 2, 0, MPI_COMM_WORLD, NULL);
                assert_fail |= assert_fail1 || assert_fail2;
                change |= SDK_Apply(kMATRIX, tmp_arr1) || SDK_Apply(kMATRIX, tmp_arr2);
                count++;
            }
            else if (comm_rank == 1) {
                SDK_Mark_Horizontal_Availables(kMATRIX, assert_fail, 0, SIZE);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&assert_fail, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD);
            }
            else if (comm_rank == 2) {
                SDK_Mark_Subbox_Availables(kMATRIX, assert_fail, 0, SIZE);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                MPI_Send(&assert_fail, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD);
            }
            else {
                break;
            }
            MPI_Bcast(&assert_fail, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
            if (assert_fail) break;
            MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
            if (!change) {
                // long ranger
                if (comm_rank == 0) {
                    change = SDK_Mark_Vertical_Availables_Long_Ranger(kMATRIX, 0, SIZE);
                    // cout << "SDK_Mark_Vertical_Availables_Long_Ranger" << endl;
                    int32_t tmp_arr[SIZE*SIZE];
                    MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                    bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
                    MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                    bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
                    change |= change_1 || change_2;
                }
                else if (comm_rank == 1) {
                    SDK_Mark_Horizontal_Availables_Long_Ranger(kMATRIX, 0, SIZE);
                    MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }
                else if (comm_rank == 2) {
                    SDK_Mark_Subbox_Availables_Long_Ranger(kMATRIX, 0, SIZE);
                    MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }
                else {
                    break;
                }
                MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
                if (!change) {
                    // twin
                    if (comm_rank == 0) {
                        change = SDK_Mark_Vertical_Availables_Twins(kMATRIX, 0, SIZE);
                        // cout << "SDK_Mark_Vertical_Availables_Twins" << endl;
                        int32_t tmp_arr[SIZE*SIZE];
                        MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                        bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
                        MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                        bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
                        change |= change_1 || change_2;
                    }
                    else if (comm_rank == 1) {
                        SDK_Mark_Horizontal_Availables_Twins(kMATRIX, 0, SIZE);
                        MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    }
                    else if (comm_rank == 2) {
                        SDK_Mark_Subbox_Availables_Twins(kMATRIX, 0, SIZE);
                        MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    }
                    else {
                        break;
                    }
                    MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
                    MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
                    if (!change) {
                        // triplets
                        if (comm_rank == 0) {
                            change = SDK_Mark_Vertical_Availables_Triplets(kMATRIX, 0, SIZE);
                            // cout << "SDK_Mark_Vertical_Availables_Triplets" << endl;
                            int32_t tmp_arr[SIZE*SIZE];
                            MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                            bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
                            MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                            bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
                            change |= change_1 || change_2;
                        }
                        else if (comm_rank == 1) {
                            SDK_Mark_Horizontal_Availables_Triplets(kMATRIX, 0, SIZE);
                            MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                        }
                        else if (comm_rank == 2) {
                            SDK_Mark_Subbox_Availables_Triplets(kMATRIX, 0, SIZE);
                            MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                        }
                        else {
                            break;
                        }
                        MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
                        MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
                        if (!change) {
                            if (comm_rank == 0) {
                                int32_t start_idx = 0;
                                while (start_idx < SIZE*SIZE && is_field_literal(kMATRIX[start_idx]))
                                    start_idx++;
                                if (start_idx == SIZE*SIZE)
                                    break;
                                SDK_Permutations(kMATRIX, stack, start_idx, start_idx + 5);
                            }
                            break;
                        }
                    }
                }
            }
            if (comm_rank == 0) {
                conflict = is_conflict(kMATRIX);
            }
            MPI_Bcast(&conflict, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
        }
        if (SDK_Check_Breakdown(kMATRIX) && !is_conflict(kMATRIX)) {
            break;
        }
        if (comm_rank == 0) {
            if (stack.empty()) {
                finish = true;
                MPI_Send(&finish, 1, MPI_C_BOOL, 1, 0, MPI_COMM_WORLD);
                MPI_Send(&finish, 1, MPI_C_BOOL, 2, 0, MPI_COMM_WORLD);
                break;
            }
            else {
                MPI_Send(&finish, 1, MPI_C_BOOL, 1, 0, MPI_COMM_WORLD);
                MPI_Send(&finish, 1, MPI_C_BOOL, 2, 0, MPI_COMM_WORLD);
                tmp = stack.back(); stack.pop_back();
                memcpy(kMATRIX, tmp, SIZE*SIZE*sizeof(int32_t));
                delete []tmp;
            }
        }
        else {
            MPI_Recv(&finish, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD, NULL);
            if (finish) break;
        }
        MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    if (comm_rank == 0) {
        double duration = MPI_Wtime() - time_start;
        cout << "p:" << comm_size << "\nRunning time:" << duration << endl;
    }

    // cout << "Total number of cores: " << max_threads << endl;
    // cout << "Maximum value: " << M << endl;
    // cout << "Time: " << (end_time - start_time) << endl;

    return 0;
}
