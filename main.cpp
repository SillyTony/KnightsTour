#include <iostream>
#include "stack.h"
#include "tile.h"
#include "knight.h"
#include "chessboard.h"
#include <conio.h>
#include <ctime>

using namespace std;

int main()
{
    char key;
    do
    {
        Knight stackKnight, queueKnight;
        cin>>stackKnight;
        queueKnight = stackKnight;
        time_t start = clock(), end;
        stackKnight.moveStack();
        end = clock();
        cout<<"The stack took "<<float(end-start)/CLOCKS_PER_SEC<<" to complete."<<endl;
        start = clock();
        queueKnight.moveQueue();
        end = clock();
        cout<<"The queue took "<<float(end-start)/CLOCKS_PER_SEC<<" to complete."<<endl;
        stackKnight.printStack();
        queueKnight.printQueue();
        cout<<"Do you wish to choose a new starting position. Hit y to continue."<<endl;
        key = _getch();
        system("cls");
    }while(key == 'y');

    return 0;
}
