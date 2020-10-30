#!/bin/bash

#SBATCH --error=15core_result_parallel_nqueen.err
#SBATCH --output=15core_result_parallel_nqueen.out
#SBATCH --partition=snowy
#SBATCH --time=0:40:00
#SBATCH --nodes=1-1
#SBATCH --cpus-per-task=1
#SBATCH --ntasks-per-node=15
#SBATCH --mem=32G #SBATCH --job-name=parallel_tianyim 
# You need to load a compiler before openmpi.
module load gcc/8.3.0
module load openmpi/3.1.4 

mpicxx -std=c++14 -fopenmp -o parallel_n_queens ../parallel_n_queens.cpp -O3
mpirun -np 15 parallel_n_queens 16
