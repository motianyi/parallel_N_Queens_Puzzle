
#include <stdio.h>
#include <iostream>
#include <stdlib.h>		
bool validChessBoard(int n, int** chessboard, int row, int col);
bool placeQueen(int n, int** chessboard, int col);
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
    
    // get the number of n from command line
	int n = atoi(argv[1]);

    // integer devision and round up
	int problems = (n+1)/2;
    printf("%d\n", problems);

	
    int **allChessboard[problems];
	for(int i = 0; i < problems; i++){
        allChessboard[i] = new int*[n];
	    for(int j = 0; j < n; j++){
            allChessboard[i][j] = new int[n];

	    	// for(int k = 0; k < n; k++){
	        // 	chessboards[i][j][k] = 0;
	    	// }
	    }

        int** chessboard = allChessboard[i];
        chessboard[i][0] = 1;
        placeQueen(n, chessboard, 1);
	}

    // int **chessboards[problems];
	// for(int i = 0; i < problems; i++){
    //     int** chessboard = new int*[n];
	//     for(int j = 0; j < n; j++){
    //         chessboard[j] = new int[n];


    //     chessboard[i][0] = 1;
    //     placeQueen(n, chessboard, 1);
	// }


	std::cout << "There is "<<solutionCount << " solutions for " << n << " Queen puzzle. \n" ;
	   
	return 0;
}