#!/bin/bash

#SBATCH --error=@result_parallel_nqueen-%j.err
#SBATCH --output=@result_parallel_nqueen-%j.out
#SBATCH --partition=snowy
#SBATCH --time=0:40:00
#SBATCH --nodes=@-@
#SBATCH --cpus-per-task=16
#SBATCH --ntasks-per-node=1 
#SBATCH --mem=32G #SBATCH --job-name=parallel_tianyim 
# You need to load a compiler before openmpi.
module load gcc/8.3.0
module load openmpi/3.1.4 

mpicxx -std=c++14 -fopenmp -o parallel_n_queens ../parallel_n_queens.cpp -O3
mpirun -np @ parallel_n_queens 16
