#include "knight.h"

Knight::Knight()
{
    nukeKnight();
}

Knight::Knight(int m,  int n)
{
    setPosition(m, n);
    setStartPosition(m,n);
    mainBoard.createBoard(8,8);
}

Knight::~Knight()
{
    nukeKnight();
}

Knight::Knight(const Knight& other)
{
    copyKnight(other);
}

Knight& Knight::operator=(const Knight& other)
{
    if(this != & other)
    {
        nukeKnight();
        copyKnight(other);
    }
    return *this;
}

void Knight::moveStack()
{
    Cord temp;

    backtrackStack.resize(mainBoard.returnCol()*mainBoard.returnRow());
    initilizeMoves();
    backtrackStack.push(startPosition);
    mainBoard.changeBool(startPosition.x,startPosition.y,true);

    while(backtrackStack.size() != (mainBoard.returnCol() * mainBoard.returnRow()))
    {
        backTrackCheck = false;
        calculatePossibleMoves(position);
        temp = checksSmallestMoves(position);

        while(backTrackCheck)
        {
            backTrackingStack();
            while(mainBoard.returnBackTrackCount(position.x,position.y) == mainBoard.returnMoves(position.x,position.y))
            {
                mainBoard.changeBackTrackCount(position.x,position.y,0);
                setAllToFalse(position);
                backTrackingStack();
            }
            temp = findNextSmallest(position);
        }
        setPosition(temp.x,temp.y);
        backtrackStack.push(position);
        mainBoard.changeBool(position.x,position.y, true);
    }
}

void Knight::moveQueue()
{
    Cord temp;
    int x = 64;
    queue.resize(mainBoard.returnCol()*mainBoard.returnRow());
    initilizeMoves();
    queue.enqueue(startPosition,x);
    x--;
    mainBoard.changeBool(startPosition.x,startPosition.y,true);
    while(queue.size() != (mainBoard.returnCol() * mainBoard.returnRow()))
    {
        backTrackCheck = false;
        calculatePossibleMoves(position);
        temp = checksSmallestMovesQueue(position);
        while(backTrackCheck)
        {
            backTrackingQueue();
            x++;
            while(mainBoard.returnBackTrackCount(position.x,position.y) == mainBoard.returnMoves(position.x,position.y))
            {
                mainBoard.changeBackTrackCount(position.x,position.y,0);
                setAllToFalse(position);
                backTrackingQueue();
                x++;
            }
            temp = findNextSmallestQueue(position);
        }
        setPosition(temp.x,temp.y);
        queue.enqueue(position,x);
        x--;

        mainBoard.changeBool(position.x,position.y, true);
    }
}

void Knight::backTrackingStack()
{
    mainBoard.changeBool(position.x,position.y,false);
    mainBoard.changeBackTrack(position.x,position.y,true);
    backtrackStack.pop();
    position = backtrackStack.top();
    mainBoard.changeBackTrackCount(position.x,position.y,mainBoard.returnBackTrackCount(position.x,position.y)+1);
}

void Knight::backTrackingQueue()
{
    mainBoard.changeBool(position.x,position.y,false);
    mainBoard.changeBackTrack(position.x,position.y,true);
    queue.dequeue();
    position = queue.front();
    mainBoard.changeBackTrackCount(position.x,position.y,mainBoard.returnBackTrackCount(position.x,position.y)+1);
}

int Knight::calculateNumberOfMoves(int a, int b)
{
    int count = 0;

    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(a+it->first,b+it->second))
            count++;
    return count;
}

void Knight::calculatePossibleMoves(Cord coordinate)
{
    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(coordinate.x+it->first,coordinate.y+it->second))
            mainBoard.changeMove(coordinate.x+it->first, coordinate.y+it->second, calculateNumberOfMoves(coordinate.x+it->first,coordinate.y+it->second));

}

Cord& Knight::checksSmallestMoves(Cord j)
{
    int count = 8;
    Cord temp;

    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(j.x+it->first,j.y+it->second))
            if(mainBoard.returnMoves(j.x+it->first,j.y+it->second) <= count)
            {
                count = mainBoard.returnMoves(j.x+it->first,j.y+it->second);
                temp.x = j.x+it->first;
                temp.y = j.y+it->second;
            }
    if(count == 0 && (backtrackStack.size()+1 != backtrackStack.capacity()))
        backTrackCheck = true;
    return temp;
}

Cord& Knight::checksSmallestMovesQueue(Cord j)
{
    int count = 8;
    Cord temp;

    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(j.x+it->first,j.y+it->second))
            if(mainBoard.returnMoves(j.x+it->first,j.y+it->second) <= count)
            {
                count = mainBoard.returnMoves(j.x+it->first,j.y+it->second);
                temp.x = j.x+it->first;
                temp.y = j.y+it->second;
            }
    if(count == 0 && (queue.size()+1 != queue.capacity()))
        backTrackCheck = true;
    return temp;
}


Cord& Knight::findNextSmallest(Cord j)
{
    int count = 8;
    Cord temp;

    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(j.x+it->first,j.y+it->second) && !mainBoard.returnBackTrack(j.x+it->first,j.y+it->second))
            if(mainBoard.returnMoves(j.x+it->first,j.y+it->second) <= count)
            {
                count = mainBoard.returnMoves(j.x+it->first,j.y+it->second);
                temp.x = j.x+it->first;
                temp.y = j.y+it->second;
            }

    if(count == 0 && (backtrackStack.size()+1 != backtrackStack.capacity()))
        backTrackCheck = true;
    else
        backTrackCheck = false;

    return temp;
}

Cord& Knight::findNextSmallestQueue(Cord j)
{
    int count = 8;
    Cord temp;

    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(j.x+it->first,j.y+it->second) && !mainBoard.returnBackTrack(j.x+it->first,j.y+it->second))
            if(mainBoard.returnMoves(j.x+it->first,j.y+it->second) <= count)
            {
                count = mainBoard.returnMoves(j.x+it->first,j.y+it->second);
                temp.x = j.x+it->first;
                temp.y = j.y+it->second;
            }

    if(count == 0 && (queue.size()+1 != queue.capacity()))
        backTrackCheck = true;
    else
        backTrackCheck = false;

    return temp;
}

void Knight::setAllToFalse(Cord j)
{
    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(legal(j.x+it->first,j.y+it->second))
            mainBoard.changeBackTrack(j.x+it->first,j.y+it->second, false);
}

bool Knight::closedOrOpen()
{
    for(vector<pair<int,int> >::iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it)
        if(position.x+it->first == startPosition.x && position.y+it->second == startPosition.y)
            return true;
    return false;
}

bool Knight::legal(int a, int b)
{
    return (((a < mainBoard.returnRow()) && (a >= 0) && (b >= 0)  && (b  < mainBoard.returnCol())) && !(mainBoard.returnBool(a,b)));
}

void Knight::initilizeMoves()
{
    possibleMoves.push_back(pair<int,int>(2,1));
    possibleMoves.push_back(pair<int,int>(1,2));
    possibleMoves.push_back(pair<int,int>(-1,2));
    possibleMoves.push_back(pair<int,int>(-2,1));
    possibleMoves.push_back(pair<int,int>(-2,-1));
    possibleMoves.push_back(pair<int,int>(-1,-2));
    possibleMoves.push_back(pair<int,int>(1,-2));
    possibleMoves.push_back(pair<int,int>(2,-1));
}

void Knight::setPosition(int m, int n)
{
    try
    {
        if((m < 0) || (m >= mainBoard.returnRow()) || (n < 0) ||(n >= mainBoard.returnCol()))
            throw OUTBOUNDS;

        position.x = m;
        position.y = n;
    }
    catch(KnightE)
    {
    }
}

void Knight::setStartPosition(int i, int j)
{
    try
    {
        if((i < 0) || (i >= mainBoard.returnRow()) || (j < 0) ||(j >= mainBoard.returnCol()))
            throw OUTBOUNDS;

        startPosition.x = i;
        startPosition.y = j;
    }
    catch(KnightE)
    {
        cout<<"Bad position"<<endl;
        exit(0);
    }
}

void Knight::copyKnight(const Knight& other)
{
    setPosition(other.position.x, other.position.y);
    setStartPosition(other.startPosition.x,other.startPosition.y);
    mainBoard.createBoard(8,8);
}

void Knight::nukeKnight()
{
    setPosition(0,0);
    setStartPosition(0,0);
    possibleMoves.clear();
}

void Knight::printStack()
{
    char key;
    cout<<"Do you wish to print out the tour. Hit y to continue. "<<endl;
    key = _getch();
    if(key == 'y')
        while(!backtrackStack.empty())
        {
            Cord temp = backtrackStack.top();
            cout<<"(N"<<char(temp.x+97)<<temp.y+1<<") ";
            backtrackStack.pop();
        }
    if(closedOrOpen())
        cout<<endl<<"The Tour is closed"<<endl;
    else
        cout<<endl<<"The Tour is open"<<endl;
}

void Knight::printQueue()
{
    cout<<queue.front()<<endl;
    while(!queue.empty())
    {
        Cord temp = queue.front();
        cout<<"(N"<<char(temp.x+97)<<temp.y+1<<") ";
        queue.dequeue();
    }
    cout<<endl;
}

bool Knight::getInput(string& line)
{
    cout<<"Please input the position for the knight in LETTER NUMBER form for a 8x8 board: ";
    getline(cin, line);
    return !line.empty();
}

ostream& operator<<(ostream& out,  Knight& item)
{
    while(!item.backtrackStack.empty())
    {
        out<<item.backtrackStack.top();
        item.backtrackStack.pop();
    }
    if(item.closedOrOpen())
        out<<endl<<"The Tour is closed"<<endl;
    else
        out<<endl<<"The Tour is open"<<endl;
    return out;
}

istream& operator>>(istream& in, Knight& item)
{
    char m;
    int n, c;
    string line;
    stringstream ss;
    if(item.getInput(line))
    {
        while(line.size() != 2 || (line[0] < 65 || (line[0] > 72 && line[0] < 97) || line[0] > 104)
              || line[1] == '0' || line[1] == '9' || !isdigit(line[1]))
        {
            cout<<"Please try again. "<<endl;
            item.getInput(line);
            if(line.empty())
                exit(0);
        }
        ss<<line;
        ss>>m>>n;
        m = toupper(m);
        c = int(m)-65;
        n--;
        item.setPosition(c,n);
        item.setStartPosition(c,n);
        item.mainBoard.createBoard(8,8);
    }
    else
        exit(0);
    return in;
}
