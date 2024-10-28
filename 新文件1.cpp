// �ƿW

#include <iostream>
#include <vector>
using namespace std;

const int N = 9; // 9*9

bool isSafe(vector<vector<int>>& board, int row, int col, int num){
	
	for(int x = 0; x < N; x++){
		// look for row
		if (board[row][x] == num) return false;
	}	
	
	for(int x = 0; x < N; x++){
		// look for colum
		if (board[x][col] == num) return false;
	}
	
	int startRow = row - row % 3;
	int startCol = col - col % 3;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i + startRow][j + startCol] == num) return false;
		}
	}
	
	return true; 
}


bool solveSudoku(vector<vector<int>>& board) {
	int row = -1;
	int col = -1;
	bool isEmpty = false;
	
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if(board[i][j] == 0){
				row = i;
				col = j;
				isEmpty = true;
				break;
			}
		}
		if(!isEmpty) break;
	}
	
	if(!isEmpty) return true;
	
	for (int num = 1; num <= 9; num++){
		if(isSafe(board, row, col, num)){
			board[row][col] = num;
			
			if(solveSudoku(board)) return true;
			
			board[row][col] = 0;
		}
	}
	
	return false;
	
}

// ��ܼƿW�ѽL
void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        printBoard(board);
    } else {
        cout << "No solution exists";
    }

    return 0;
}




























 
