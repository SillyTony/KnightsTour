#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Tile
{
    public:
        Tile();
        ~Tile();
        Tile(const Tile& other);
        Tile& operator=(const Tile& other);

        int getMoveCount();
        int getBackTrackCount();
        bool getVisit();
        bool getBackTrack();

        void setMoveCount(int m);
        void setBool(bool v);
        void setBackTrack(bool v);
        void setBackTrackCount(int a);

        friend
        ostream& operator<<(ostream& out, const Tile& item);

        friend
        istream& operator>>(istream& in, Tile& item);

    private:
        bool visit, backTrack;
        int moveCount,backTrackCount;

        void nukem();
        void copy(const Tile& other);
};

#endif // TILE_H
