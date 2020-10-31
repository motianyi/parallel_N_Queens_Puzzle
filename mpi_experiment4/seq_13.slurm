#!/bin/bash

#SBATCH --error=err/13result_seq_nqueen.err
#SBATCH --output=out/13result_seq_nqueen.out
#SBATCH --partition=snowy
#SBATCH --time=0:40:00
#SBATCH --nodes=1-1
#SBATCH --cpus-per-task=1
#SBATCH --ntasks-per-node=1 
#SBATCH --mem=32G #SBATCH --job-name=parallel_tianyim 
# You need to load a compiler before openmpi.
module load gcc/8.3.0
module load openmpi/3.1.4 

g++ -std=c++14 -fopenmp -o n_queens ../n_queens.cpp -O3

time ./n_queens 13
