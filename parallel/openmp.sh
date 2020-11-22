#!/bin/bash

# (See https://arc-ts.umich.edu/greatlakes/user-guide/ for command details)

# Set up batch job settings
#SBATCH --job-name=mpi_demo_jobl
#SBATCH --mail-type=BEGIN,END
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --mem-per-cpu=1g 
#SBATCH --time=00:05:00
#SBATCH --account=eecs587f20_class
#SBATCH --partition=standard

# Run your program
# (">" redirects the print output of your program,
#  in this case to "mpi_demo_output.txt")
mpirun -np 4 ./build/sudoku_mpi ../testcases/9x9_easy1.txt > output.txt
