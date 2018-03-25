#include "chessboard.h"

ChessBoard::ChessBoard()
{
    createBoard(8,8);
}

ChessBoard::ChessBoard(int m, int n)
{
    createBoard(m,n);
}

ChessBoard::~ChessBoard()
{
    cleanBoard();
}

ChessBoard::ChessBoard(const ChessBoard& other)
{
    copyBoard(other);
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
    if(this != &other)
    {
        cleanBoard();
        copyBoard(other);
    }
    return *this;
}

int ChessBoard::returnRow()
{
    return boardRow;
}

int ChessBoard::returnCol()
{
    return boardCol;
}

int ChessBoard::returnMoves(int a, int b)
{
    return board[a][b].getMoveCount();
}

int ChessBoard::returnBackTrackCount(int a, int b)
{
    return board[a][b].getBackTrackCount();
}

bool ChessBoard::returnBool(int a, int b)
{
    return board[a][b].getVisit();
}

bool ChessBoard::returnBackTrack(int a, int b)
{
    return board[a][b].getBackTrack();
}

void ChessBoard::changeBool(int a, int b, bool p)
{
    board[a][b].setBool(p);
}

void ChessBoard::changeMove(int a, int b, int c)
{
    board[a][b].setMoveCount(c);
}

void ChessBoard::changeBackTrackCount(int a, int b, int c)
{
    board[a][b].setBackTrackCount(c);
}

void ChessBoard::changeBackTrack(int a, int b, bool c)
{
    board[a][b].setBackTrack(c);
}

void ChessBoard::cleanBoard()
{
    for(int j = 0; j < boardRow; j++)
        delete [] board[j];
    delete[]board;
    boardRow = 0;
    boardCol = 0;
}

void ChessBoard::createBoard(int m, int n)
{
    try
    {
        if(m < 5 || n < 5)
            throw BAD_SIZE;
        boardRow = m;
        boardCol = n;
        board = new Tile*[boardRow];
        for(int i = 0; i < boardRow; i++)
            board[i] = new Tile[boardCol];
    }
    catch(CHESSERROR)
    {
        cout<<"Invalid Board Size. Creating a standard Board"<<endl;
        createBoard(8,8);
    }
}

void ChessBoard::copyBoard(const ChessBoard& other)
{
    createBoard(other.boardRow, other.boardCol);
}

ostream& operator<<(ostream& out, const ChessBoard& other)
{
    for(int i = 0; i < other.boardRow; i++)
    {
        for(int j = 0; j < other.boardCol; j++)
            out<<other.board[i][j];
        out<<endl;
    }
    return out;
}

istream& operator>>(istream& in, ChessBoard& other)
{
    int row, col;
    cout<<"Input row of the board: ";
    in>>row;
    cout<<"Input col of the board: ";
    in>>col;
    other.createBoard(row, col);
    return in;
}
