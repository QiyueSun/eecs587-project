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
#include "util.h"
#include "vertical.h"
#include "horizontal.h"
#include "subbox.h"
#include "breakdown.h"

using namespace std;

int main(int argc, char *argv[]) {
    vector<int64_t> kMATRIX;
    kMATRIX.resize(SIZE * SIZE, 0);
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
        is_master = true;
        time_start = MPI_Wtime();
    }

retry:
    if (comm_rank == 0) {
        SDK_Mark_Vertical_Availables(kMATRIX);
        // SDK_Pretty_Print(kMATRIX);

        vector<int64_t> tmp(SIZE * SIZE, 0);

        MPI_Recv(tmp.data(), SIZE * SIZE, MPI_LONG, 1, 0, MPI_COMM_WORLD, NULL);
        SDK_Apply(kMATRIX, tmp);
        MPI_Recv(tmp.data(), SIZE * SIZE, MPI_LONG, 2, 0, MPI_COMM_WORLD, NULL);
        SDK_Apply(kMATRIX, tmp);
    }
    else if (comm_rank == 1) {
        SDK_Mark_Horizontal_Availables(kMATRIX);
        // cout << "id = 1\n";
        // SDK_Pretty_Print(kMATRIX);
        // cout << "\n";

        MPI_Send(kMATRIX.data(), SIZE * SIZE, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }
    else if (comm_rank == 2) {
        SDK_Mark_Subbox_Availables(kMATRIX);
        // cout << "id = 2\n";
        // SDK_Pretty_Print(kMATRIX);
        // cout << "\n";

        MPI_Send(kMATRIX.data(), SIZE * SIZE, MPI_LONG, 0, 0, MPI_COMM_WORLD);
    }
    else {
        goto bailout;
    }

    MPI_Bcast(kMATRIX.data(), SIZE * SIZE, MPI_LONG, 0, MPI_COMM_WORLD);

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
