#include <iostream>
using namespace std;

class Board
{
public:
    char board[3][3];

    // Returns an empty board (Board with all -1s)
    void clearBoard();
    //  Displays the current state of board
    void displayBoard();
    // Checks if there is a winner
    char checkWinner();
    // Checks if the board is full
    bool checkFull();
};

class Player
{
    public:
    // Checks if the move is valid i.e whether there is already a mark on that place
    bool valid(int x, int y, Board& B);
    // Implements the move
    void move(int x, int y, Board& B);
};

class Computer 
{
    public:
    // Decides the best possible move
    pair<int, int> MinMax(Board& B, bool MaxScore, int depth);
};
