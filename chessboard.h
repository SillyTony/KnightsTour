#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "tile.h"

enum CHESSERROR{BAD_SIZE};

class ChessBoard
{
    public:
        ChessBoard();
        ChessBoard(int m, int n);
        ~ChessBoard();
        ChessBoard(const ChessBoard& other);
        ChessBoard& operator=(const ChessBoard& other);

        int returnRow();
        int returnCol();
        int returnMoves(int a, int b);
        int returnBackTrackCount(int a, int b);
        bool returnBackTrack(int a, int b);
        bool returnBool(int a, int b);

        void changeMove(int a, int b, int c);
        void changeBackTrackCount(int a, int b, int c);
        void changeBackTrack(int a, int b, bool c);
        void changeBool(int a, int b, bool p);
        void createBoard(int m, int n);
        void cleanBoard();

        friend
        ostream& operator<<(ostream& out, const ChessBoard& other);

        friend
        istream& operator>>(istream& in, ChessBoard& other);

    private:
        Tile** board;
        int boardRow, boardCol;

        void copyBoard(const ChessBoard& other);
};

#endif // CHESSBOARD_H
