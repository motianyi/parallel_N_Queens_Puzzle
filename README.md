# parallel_N_Queens_Puzzle

Commands to run on Mac OS
```
# complie
g++ -O3 -o n_queens n_queens.cpp

# execute

./seq_n-queens_cpp 14
```
```
# parallel complie
mpic++ -o parallel_n_queens parallel_n_queens.cpp -O3 -std=c++14

# parallel execute
mpirun -n 6 ./n-queens_cpp 14
```

Commands to run on Linux (Spartan Cluster)
```
# complie
g++ -O3 -o n_queens n_queens.cpp

# execute

./seq_n-queens_cpp 14
```