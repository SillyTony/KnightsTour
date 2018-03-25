#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <cctype>
#include <conio.h>
#include <string>
#include <sstream>
#include "stack.h"
#include "chessboard.h"
#include "queue.h"

using namespace std;

enum KnightE{OUTBOUNDS};

struct Cord
{
    int x;
    int y;

    Cord& operator=(const Cord& other)
    {
        if(this != & other)
        {
            x = other.x;
            y =other.y;
        }
        return *this;
    }

    friend
    ostream& operator<<(ostream& out, const Cord& item)
    {
        out<<"("<<item.x<<","<<item.y<<") ";
        return out;
    }
};

class Knight
{
    public:
        Knight();
        Knight(int m, int n);
        ~Knight();
        Knight(const Knight& other);
        Knight& operator=(const Knight& other);

        void setPosition(int m, int n);
        void setAllToFalse(Cord j);
        void moveStack();
        void moveQueue();
        void backTrackingStack();
        void backTrackingQueue();

        bool legal(int a, int b);
        bool closedOrOpen();

        Cord& checksSmallestMoves(Cord j);
        Cord& findNextSmallest(Cord j);
        Cord& checksSmallestMovesQueue(Cord j);
        Cord& findNextSmallestQueue(Cord j);


        void calculatePossibleMoves(Cord coordinate);
        int calculateNumberOfMoves(int a, int b);

        void printStack();
        void printQueue();
        void setStartPosition(int i, int j);
        bool getInput(string& line);

        friend
        ostream& operator<<(ostream& out,  Knight& item);

        friend
        istream& operator>>(istream& in, Knight& item);

    private:
        ChessBoard mainBoard;
        Cord position, startPosition;
        Stack<Cord> backtrackStack;
        pQueue<Cord,int> queue;
        vector<pair<int,int> > possibleMoves;
        bool backTrackCheck;

        void initilizeMoves();
        void nukeKnight();
        void copyKnight(const Knight& other);
};

#endif // KNIGHT_H
