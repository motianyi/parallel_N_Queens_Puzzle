#include <stdio.h>
#include <iostream>
#include <stdlib.h>		
#include <mpi.h>


bool validChessBoard(int n, int** board, int row, int col);
bool placeQueen(int n, int** board, int col);

int solutionCount = 0; 


//Check all constrains, one queen on each row, one queen each digonal
// there is no needs to cleck queen on the same column because it is 
//guranteed by the algorithm.
bool validChessBoard(int n, int** chessboard, int row, int col){
    // check whether is no queen on same row of (row, col)
    
    for (int i = 0; i < col; i++)
        if (chessboard[row][i])
            return false;

    // check whether these is no queen on the upper-left to bottom-right diagonal
    int r = row;
    int c = col;
    
    while(r >= 0 && c >= 0){
        if (chessboard[r][c]){
            return false;
        }
        r -= 1,
        c -= 1;
    }
    
    // check whether these is no queen on the upper-right to bottom-left diagonal
    r = row;
    c = col;
    while(c >= 0 && r < n){
        if (chessboard[r][c]){
            return false;
        }
        r += 1;
        c -= 1;
    }
    return true;
}
 
bool placeQueen(int n, int** chessboard, int col){
  
    //finish placing Queens on the chessboard
    if (col == n){
        // chessboard is symmetric, count for 1
        if(n % 2 == 1 && chessboard[n/2][0] == 1){
            solutionCount += 1;  
        // chessboard asymmetric, count for 1
        }else{
            solutionCount += 2;
        }
 		return true;
    }

    //Try each row on that column
    for (int row = 0; row < n; row++){
        if (validChessBoard(n, chessboard, row, col) == true){
            
            chessboard[row][col] = 1;

            // recursively place next queen
            placeQueen(n, chessboard, col + 1);
            chessboard[row][col] = 0;
        }
    }
    return false;
}



int main(int argc, char* argv[]) {

    auto started = std::chrono::high_resolution_clock::now();
     // get the number of n from command line
    int n = atoi(argv[1]);

    int rank, world_size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

   
	
    int finishedColumn = 2;

    // calculate the number of problems
	int problems = 0;
    if(finishedColumn == 1){
        problems = (n+1)/2;
    }else if(finishedColumn == 2){
        problems = (n+1)/2 * n;
    }else{
        std::cout << "Error";
    }
    // printf("%d\n",problems);

    int **boards[problems];
    for(int i = 0; i < problems; i++){
        boards[i] = new int*[n];
        for(int j = 0; j < n; j++){
            boards[i][j] = new int[n];
            for(int k = 0; k < n; k++){
                boards[i][j][k] = 0;
            }
        }
    }

    if(finishedColumn == 1){
        // initialize the board
        for(int i = 0; i < problems; i++){
            boards[i][i][0] = 1;
            // if(rank == 0){
            //     printf("%d, %d, %d\n", i, i / n, 0);
            // }
        }

    }else if(finishedColumn ==2){
        // initialize the board
        for(int i = 0; i < problems; i++){
            boards[i][i / n][0] = 1;
            // if(rank == 0){
            //     printf("%d, %d, %d\n", i, i / n, 0);
            // }
            if(validChessBoard(n, boards[i], i % n, 1)){
                // if(rank == 0){
                //     printf("%d, %d, %d valid \n", i, i % n, 1);
                // }
                boards[i][i % n][1] = 1;
            }else{
                // if(rank == 0){
                //     printf("%d, %d, %d not valid\n", i, i % n, 1);
                // }
                boards[i][i % n][1] = 1;
                boards[i][0][0] = -1;
            }
        }
    }
        
  
    int end_signal = -1;
    
    if(rank == 0){
            
        int problem_id = 0;
        int result;

        // send a problems to each rank
        for(int i = 1; i < world_size; i++){
            MPI_Send(&problem_id, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            problem_id += 1;
        }

        // send rest problems
        while(problem_id < problems){
            MPI_Status stat;
            MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            // printf("%d\n", result);
            // printf("%d\n", problem_id);
            // send the next problem index to that rank 
            MPI_Send(&problem_id, 1, MPI_INT, stat.MPI_SOURCE, 0, MPI_COMM_WORLD);
            
            problem_id += 1;
        }


        //collect the results and send stop signal to other processes
        int count = 0;
        while(count < world_size-1){
            MPI_Status stat;
            MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
        
            MPI_Send(&end_signal, 1, MPI_INT, stat.MPI_SOURCE, 0, MPI_COMM_WORLD);
            count += 1;
        }
    }else{
        int problem_id;
   
        while(true){
            int message = 0;

            //receive the result from rank 0
            MPI_Status stat;
            MPI_Recv(&problem_id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);

            if(problem_id == end_signal){ 
                break;

            }else{
                // do calculation
                if(boards[problem_id][0][0] != -1){
                    placeQueen(n, boards[problem_id], finishedColumn);
                }         
            }
            // inform the root it has finished the calculation
            MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }

    

    }

    int local_sum = solutionCount;

    // Reduce all of the local sums into global sum
    int *global_sum = new int[n];
    MPI_Reduce(&local_sum, global_sum, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    //root node print the result message
    if(rank == 0){
        std::cout << "There is "<<*global_sum << " solutions for " << n << " Queen puzzle. (Parallel N Queen)\n" ;
    }
    free(global_sum);


    MPI_Finalize();
    auto done = std::chrono::high_resolution_clock::now(); 
    if(rank == 0){
        std::cout << "runtime: " << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count()/1000.0 <<" seconds.\n";
    }
    return 0;
}
