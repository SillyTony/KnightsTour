#include "tile.h"

Tile::Tile()
{
    visit = false;
    backTrack = false;
    moveCount = 8;
    backTrackCount = 0;
}

Tile::~Tile()
{
    nukem();
}

Tile::Tile(const Tile& other)
{
    copy(other);
}

Tile& Tile::operator=(const Tile& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

int Tile::getMoveCount()
{
    return moveCount;
}

int Tile::getBackTrackCount()
{
    return backTrackCount;
}

bool Tile::getVisit()
{
    return visit;
}

bool Tile::getBackTrack()
{
    return backTrack;
}

void Tile::setMoveCount(int move)
{
    moveCount = move;
}

void Tile::setBackTrackCount(int bTCount)
{
    backTrackCount = bTCount;
}

void Tile::setBool(bool v)
{
    visit = v;
}

void Tile::setBackTrack(bool v)
{
    backTrack = v;
}

void Tile::copy(const Tile& other)
{
    visit = other.visit;
    moveCount = other.moveCount;
}

void Tile::nukem()
{
    visit = false;
    backTrack = false;
    moveCount = 8;
    backTrackCount = 0;
}

ostream& operator<<(ostream& out, const Tile& item)
{
    out<<item.visit;
    return out;
}

istream& operator>>(istream& in, Tile& item)
{
    if(in == cin)
    {
        cout<<"Number of moves :";
        in>>item.moveCount;
    }
    else
        in>>item.moveCount;
    return in;
}
