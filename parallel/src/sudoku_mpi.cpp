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


retry:
    if (comm_size < 6) {
        if (comm_rank == 0) {
            change = SDK_Mark_Vertical_Availables(kMATRIX, assert_fail, 0, SIZE);

            int32_t tmp_arr1[SIZE*SIZE];
            int32_t tmp_arr2[SIZE*SIZE];
            bool assert_fail1 = false;
            bool assert_fail2 = false;
            MPI_Recv(tmp_arr1, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
            MPI_Recv(assert_fail1, 1, MPI_BOOL, 1, 0, MPI_COMM_WORLD, NULL);
            MPI_Recv(tmp_arr2, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
            MPI_Recv(assert_fail2, 1, MPI_BOOL, 2, 0, MPI_COMM_WORLD, NULL);
            
            if (assert_fail0 || assert_fail1 || assert_fail2) {
                
            }
            change |= SDK_Apply(kMATRIX, tmp_arr1) || SDK_Apply(kMATRIX, tmp_arr2);
            count++;
        }
        else if (comm_rank == 1) {
            SDK_Mark_Horizontal_Availables(kMATRIX, assert_fail, 0, SIZE);
            MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(assert_fail, 1, MPI_BOOL, 0, 0, MPI_COMM_WORLD);
        }
        else if (comm_rank == 2) {
            SDK_Mark_Subbox_Availables(kMATRIX, assert_fail, 0, SIZE);
            MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(assert_fail, 1, MPI_BOOL, 0, 0, MPI_COMM_WORLD);
        }
        else {
            goto bailout;
        }
    }
    else if (comm_size < 12) {
        switch (comm_rank) {
            case 0: {
                change = SDK_Mark_Vertical_Availables(kMATRIX, 0, SIZE);
                int32_t tmp_arr[SIZE*SIZE];
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
                change = change || change_1 || change_2;
                break;
            }
            case 1: {
                SDK_Mark_Horizontal_Availables(kMATRIX, 0, SIZE/2+1);
                int32_t tmp_arr[SIZE*SIZE];
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 3, 0, MPI_COMM_WORLD, NULL);
                bool change_3 = SDK_Apply(kMATRIX, tmp_arr);
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 4, 0, MPI_COMM_WORLD, NULL);
                bool change_4 = SDK_Apply(kMATRIX, tmp_arr);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                break;
            }
            case 2: {
                SDK_Mark_Subbox_Availables(kMATRIX, 0, SIZE/2+1);
                int32_t tmp_arr[SIZE*SIZE];
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 5, 0, MPI_COMM_WORLD, NULL);
                bool change_5 = SDK_Apply(kMATRIX, tmp_arr);
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 6, 0, MPI_COMM_WORLD, NULL);
                bool change_6 = SDK_Apply(kMATRIX, tmp_arr);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
                break;
            }
            case 3: {
                SDK_Mark_Horizontal_Availables(kMATRIX, SIZE/2+1, SIZE*3/4+1);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
                break;
            }
            case 4: {
                SDK_Mark_Horizontal_Availables(kMATRIX, SIZE*3/4+1, SIZE);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
                break;
            }
            case 5: {
                SDK_Mark_Subbox_Availables(kMATRIX, 0, SIZE/2+1);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD);
                break;
            }
            case 6: {
                SDK_Mark_Subbox_Availables(kMATRIX, 0, SIZE/2+1);
                MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD);
                break;
            }
            default:
                goto bailout;
        }
    }

    MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
    MPI_Bcast(&assert_fail, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    // long ranger
    if (!change) {
        if (comm_rank == 0) {
            change = SDK_Mark_Vertical_Availables_Long_Ranger(kMATRIX, 0, SIZE);
            cout << "SDK_Mark_Vertical_Availables_Long_Ranger" << endl;
            int32_t tmp_arr[SIZE*SIZE];
            MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
            bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
            MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
            bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
            change = change || change_1 || change_2;
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
            goto bailout;
        }

        MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

        // twin
        if (!change) {
            if (comm_rank == 0) {
                change = SDK_Mark_Vertical_Availables_Twins(kMATRIX, 0, SIZE);
                cout << "SDK_Mark_Vertical_Availables_Twins" << endl;
                int32_t tmp_arr[SIZE*SIZE];
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
                MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
                change = change || change_1 || change_2;
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
                goto bailout;
            }

            MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

            if (!change) {
                if (comm_rank == 0) {
                    change = SDK_Mark_Vertical_Availables_Triplets(kMATRIX, 0, SIZE);
                    cout << "SDK_Mark_Vertical_Availables_Triplets" << endl;
                    int32_t tmp_arr[SIZE*SIZE];
                    MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
                    bool change_1 = SDK_Apply(kMATRIX, tmp_arr);
                    MPI_Recv(tmp_arr, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
                    bool change_2 = SDK_Apply(kMATRIX, tmp_arr);
                    change = change || change_1 || change_2;
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
                    goto bailout;
                }

                MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Bcast(&change, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

                if (!change) {
                    queue<int32_t[]> stack;
                    SDK_Permutations(kMATRIX, stack, 0, SIZE);
                    for (int i=0; i<SIZE; i++) {

                    }
                    if (comm_rank == 0) {
                        cout << "This cannot be solved!" << endl;
                    }
                    goto bailout;
                }
                
            }
        }
    }

    if (SDK_Check_Breakdown(kMATRIX)) {
        if (is_master) {
            SDK_Pretty_Print(kMATRIX);
        }
    }
    else {
        goto retry;
    }

bailout:
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
