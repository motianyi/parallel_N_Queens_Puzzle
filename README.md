# parallel_N_Queens_Puzzle
This is the project3 for COMP90025 at University of Melbourne (Semester 2, 2020)
## Files
```python
report.pdf # the report of the project
n_queens.cpp # sequential C++ implementation 

parallel_n_queens.cpp #parallel C++ implementation  
   
plot folder #python scripts to plot the charts 

mpi_experiment #scripts and outputs

mpi_experiment2 #scripts (for 2 - 32 cores)
mpi_experiment2/out #outputs for mpi_experiment2

mpi_experiment3 #scripts (for 34 to 64 cores)
mpi_experiment3/out #outputs for mpi_experiment3

testing # other scripts and outputs

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