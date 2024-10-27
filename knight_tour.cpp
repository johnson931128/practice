#include <iostream>
#include <iomanip>
using namespace std;

int board[8][8] = {0};

int ktmovex[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int ktmovey[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isValidMove(int x, int y){
	return (x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == 0);
}

bool knightMove(int x, int y, int movement){
	board[x][y] = movement;
	if (movement == 64){
		return true;
	}
	
	for (int i = 0; i < 8; i++){
		int newx = x + ktmovex[i];
		int newy = y + ktmovey[i];
		if (isValidMove(newx, newy)){
			if(knightMove(newx, newy, movement + 1)){
				return true;
			}
		}		
	}
	
	board[x][y] = 0;
	return false;
}


int main()
{
    int startx, starty;
    cout << "輸入起始點：";
    cin >> startx >> starty;

    // 嘗試從給定的起始點開始遊歷
    if (knightMove(startx, starty, 1))
    {
        cout << "遊歷完成！" << endl;
    }
    else
    {
        cout << "遊歷失敗！" << endl;
    }

    // 打印棋盤
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << setw(3) << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}



