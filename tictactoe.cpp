#include "tictactoe.hpp"

void Board ::clearBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void Board ::displayBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
                cout << "   |";
        }
        cout << "\n";
        if (i < 2)
            cout << "------------------\n";
    }
}

char Board ::checkWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][1];
        else if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
        else if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return board[0][0];
        else if (board[2][0] == board[1][1] && board[1][1] == board[0][2])
            return board[2][0];
    }
    return ' ';
}

bool Board ::checkFull()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            {
                if (board[i][j] == ' ')
                    return false;
            }
        }
    }
    return true;
}

bool Player ::valid(int x, int y, Board &B)
{
    if (x < 0 || x > 2 || y < 0 || y > 2)
        return false;
    if (B.board[x][y] != ' ')
    {
        cout << "Cell is already occupied: " << B.board[x][y] << "\n";
        return false;
    }
    return true;
}

// Player will always get X in our game. O is for computer
void Player::move(int x, int y, Board &B)
{
    if (valid(x, y, B))
    {
        B.board[x][y] = 'X';
    }
}

pair<int, int> Computer ::MinMax(Board &B, bool MaxScore, int depth = 0)
{

    char winner = B.checkWinner();
    if (winner == 'X')
    {
        return {-10 + depth, -1};
    }
    else if (winner == 'O')
    {
        return {10 - depth, -1};
    }
    if (B.checkFull())
    {
        return {0, -1};
    }

    int bestScore = MaxScore ? -1000 : 1000;

    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (B.board[i][j] == ' ')
            {
                B.board[i][j] = MaxScore ? 'O' : 'X';
                int score = MinMax(B, !MaxScore, depth + 1).first;

                B.board[i][j] = ' ';
                if (MaxScore)
                {
                    if (score > bestScore) // Maximize for the AI
                    {
                        bestScore = score;
                        bestMove = {bestScore, i * 3 + j};
                    }
                }
                else
                {
                    if (score < bestScore) // Minimize for the human
                    {
                        bestScore = score;
                        bestMove = {bestScore, i * 3 + j};
                    }
                }
            }
        }
    }
    return bestMove;
}

int main()
{
    Board board;
    board.clearBoard(); // Initialize the board
    Player player;
    Computer computer;

    while (true)
    {
        board.displayBoard();
        while (true)
        {
            cout << "Enter your coordinates\n";
            int x, y;
            cin >> x >> y;
            bool check = player.valid(x, y, board);
            if (check)
            {
                player.move(x, y, board);
                break;
            }
        }

        board.displayBoard();

        char winner = board.checkWinner();
        if (board.checkWinner() != ' ')
        {
            board.displayBoard();
            cout << "Winner is " << winner << endl;
            break;
        }
        else if (board.checkFull())
        {
            cout << "It's a tie!" << endl;
            break;
        }

        pair<int, int> computerMove = computer.MinMax(board, true);
        int computerX = computerMove.second / 3; // Get row from the index
        int computerY = computerMove.second % 3; // Get column from the index
        board.board[computerX][computerY] = 'O';

        winner = board.checkWinner();
        if (board.checkWinner() != ' ')
        {
            board.displayBoard();
            cout << "Winner is " << winner << endl;
            break;
        }
        else if (board.checkFull())
        {
            cout << "It's a tie!" << endl;
            break;
        }
    }
    return 0;
}