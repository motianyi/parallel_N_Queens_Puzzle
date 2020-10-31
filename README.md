# parallel_N_Queens_Puzzle
## Files
```python
report.pdf # the report of the project
n_queens.cpp # sequential C++ implementation 

parallel_n_queens.cpp #parallel C++ implementation  
   
plot folder #python scripts to plot the charts 

mpi_experiment #scripts and outputs

mpi_experiment2 #scripts  
mpi_experiment2/out #outputs for mpi_experiment3

mpi_experiment3 #scripts and outputs
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
```

```