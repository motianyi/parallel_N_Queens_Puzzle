# parallel_N_Queens_Puzzle
Author: Tianyi Mo  

This is the project 3 for Parallel and Multicore Computing (COMP90025) at The University of Melbourne (Semester 2, 2020). This project including analysing of some popular algorithms for solving the n queen project. It implements the sequential and parallel algorithm and compare their performance. The details of the algorithm can be found in [the project report](/report.pdf).

## Files

* `report.pdf` - the report of the project

* `src`
  * `src/n_queens.cpp` - sequential C++ implementation 
  * `src/parallel_n_queens.cpp` - parallel C++ implementation  
   
* `experiment`
  * `experiment/mpi_experiment` - scripts and outputs

  * `expeeriment/mpi_experiment2` - scripts (for 2 - 32 cores)
  * `expeeriment/mpi_experiment2/out` - outputs for mpi_experiment2

  * `expeeriment/mpi_experiment3` - scripts (for 34 to 64 cores)
  * `expeeriment/mpi_experiment3/out` - outputs for mpi_experiment3
* `plot` - python scripts to visualize the performance 



## Running commands on Linux Cluster / Mac OS

Commands to run on Linux (Spartan Cluster)

1 node 32 sequential (16 queens problem)
```bash
#!/bin/bash

#SBATCH --error=result_seq_nqueen-%j.err
#SBATCH --output=result_seq_nqueen-%j.out
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

time ./n_queens 16


```

1 node 32 core (16 queens problem)
```bash
#!/bin/bash

#SBATCH --error=err/32core_result_parallel_nqueen.err
#SBATCH --output=out/32core_result_parallel_nqueen.out
#SBATCH --partition=snowy
#SBATCH --time=0:40:00
#SBATCH --nodes=1-1
#SBATCH --cpus-per-task=1
#SBATCH --ntasks-per-node=32
#SBATCH --mem=32G #SBATCH --job-name=parallel_tianyim 
# You need to load a compiler before openmpi.
module load gcc/8.3.0
module load openmpi/3.1.4 

mpicxx -std=c++14 -fopenmp -o parallel_n_queens ../parallel_n_queens.cpp -O3
mpirun -np 32 parallel_n_queens 16

```

2 node, 32 cores on each node, 64 cores total (16 queens problem)
```bash
#!/bin/bash

#SBATCH --error=err/64core_result_parallel_nqueen.err
#SBATCH --output=out/64core_result_parallel_nqueen.out
#SBATCH --partition=snowy
#SBATCH --time=0:40:00
#SBATCH --nodes=2-2
#SBATCH --cpus-per-task=1
#SBATCH --ntasks-per-node=32
#SBATCH --mem=32G #SBATCH --job-name=parallel_tianyim 
# You need to load a compiler before openmpi.
module load gcc/8.3.0
module load openmpi/3.1.4 

mpicxx -std=c++14 -fopenmp -o parallel_n_queens ../parallel_n_queens.cpp -O3
mpirun -np 64 parallel_n_queens 16

```



Commands to run on Mac OS

```
# complie
g++ -O3 -o n_queens n_queens.cpp

# execute
./seq_n-queens_cpp N
```
```
# parallel complie
mpic++ -o parallel_n_queens parallel_n_queens.cpp -O3 -std=c++14

# parallel execute
mpirun -n 6 ./parallel_n_queens N
```
