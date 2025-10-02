#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void printBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isMoveValid(char board[3][3], int row, int col) {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}

pair<int,int> autoMove(char board[3][3]) {
    vector<pair<int,int>> emptyCells;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                emptyCells.push_back({i,j});
    if(emptyCells.empty()) return {-1,-1};
    int idx = rand() % emptyCells.size();
    return emptyCells[idx];
}

bool checkWin(char board[3][3], char currentPlayer) {
        // Rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == currentPlayer &&
                board[i][1] == currentPlayer &&
                board[i][2] == currentPlayer) return true;

            if (board[0][i] == currentPlayer &&
                board[1][i] == currentPlayer &&
                board[2][i] == currentPlayer) return true;
        }
        // Diagonals
        if (board[0][0] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][2] == currentPlayer) return true;

        if (board[0][2] == currentPlayer &&
            board[1][1] == currentPlayer &&
            board[2][0] == currentPlayer) return true;
        // returns false if no one has 3 in a row
        return false;
    }

int main() {
    srand(time(0));
    bool win;
    char board[3][3];
    // initialize board
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j] = ' ';

    int numPlayers;
    cout << "Enter number of players (1 or 2): ";
    cin >> numPlayers;

    char currentPlayer = 'X';
    while (true) {
        printBoard(board);
        int row=-1, col=-1;
        if(numPlayers == 2 || (numPlayers == 1 && currentPlayer=='X')) {
            cout << "Player " << currentPlayer << ", enter row and column (0-2 0-2): ";
            cin >> row >> col;
            if(!isMoveValid(board,row,col)){
                cout << "Invalid move, try again.\n";
                continue;
            }
        } else {
            // autoplayer move
            auto move = autoMove(board);
            row = move.first;
            col = move.second;
            cout << "Computer plays at " << row << " " << col << "\n";
        }

        board[row][col] = currentPlayer;
        win = checkWin(board, currentPlayer);
        if(win){
            break;
        }    
        // switch player
        currentPlayer = (currentPlayer=='X') ? 'O' : 'X';
    }
    cout << "Player " << currentPlayer << " has won the tic-tac-toe game!";
    return 0;
}