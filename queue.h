#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include <iostream>
#include "nodequ.h"

using namespace std;

template<typename T, typename U>
class pQueue
{
    public:
        pQueue(int s = 5);
        ~pQueue();
        pQueue(const pQueue<T,U> &other);
        pQueue<T,U>& operator=(const pQueue<T,U> &other);

        bool empty();
        bool full();
        void resize(int s = 5);
        int size();
        int capacity();
        void clear();

        void enqueue(const T &d, const U &p);
        void dequeue();
        T front();

        template<typename A, typename B>
        friend
        ostream& operator<<(ostream &out, const pQueue<A,B> &pQ);

        template<typename A, typename B>
        friend
        istream& operator>>(istream &in,  pQueue<A,B> &pQ);



    private:
        nodeq<T,U> *head, *tail;
        int mySize, myCapacity;

        void nukem();
        void copy(const pQueue<T,U>&other);
};

template<typename T, typename U>
pQueue<T,U>::pQueue(int s)
{
    head = tail = NULL;
    mySize = 0;
    myCapacity = s;
}

template<typename T, typename U>
pQueue<T,U>::~pQueue()
{
    nukem();
}

template<typename T, typename U>
pQueue<T,U>::pQueue(const pQueue<T,U> &other)
{
    copy(other);
}

template<typename T, typename U>
pQueue<T,U>& pQueue<T,U>::operator=(const pQueue<T,U> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T, typename U>
bool pQueue<T,U>::empty()
{
    return !head;
}

template<typename T, typename U>
bool pQueue<T,U>::full()
{
    return mySize == myCapacity;
}

template<typename T, typename U>
int pQueue<T,U>::size()
{
    return mySize;
}

template<typename T, typename U>
int pQueue<T,U>::capacity()
{
    return myCapacity;
}

template<typename T, typename U>
void pQueue<T,U>::clear()
{
    nukem();
}

template<typename T, typename U>
T pQueue<T,U>::front()
{
    return head->returnData();
}

template<typename T, typename U>
void pQueue<T,U>::resize(int s)
{
    nodeq<T,U> *ptr;

    if(s > myCapacity)
        myCapacity = s;
    else
    {
        int times = myCapacity - s;
        for(int i = 0; i < times; ++i)
        {
            ptr = tail;
            tail = tail->nextLink();
            delete ptr;
        }
    }
}

template<typename T, typename U>
void pQueue<T,U>::enqueue(const T &d, const U &p)
{
    nodeq<T,U> *newnodeq = new nodeq<T,U>(d,p), *ptr = tail;

    if(!head)
        head = tail = newnodeq;
    else
        if(!higherPriority(*tail, *newnodeq))
        {
            tail->prevLink() = newnodeq;
            newnodeq->nextLink() = tail;
            tail = newnodeq;
        }
        else
        {
            while(ptr->nextLink() && higherPriority(*ptr->nextLink(), *newnodeq))
                ptr = ptr->nextLink();
            if(ptr->nextLink())
            {
                newnodeq->nextLink()=ptr->nextLink();
                newnodeq->nextLink()->prevLink() = newnodeq;
                newnodeq->prevLink() = ptr;
                ptr->nextLink() = newnodeq;
            }
            else
            {
                head = newnodeq;
                newnodeq->prevLink() = ptr;
                ptr->nextLink() = head;
                head->nextLink() = NULL;
            }
        }
    ++mySize;
}

template<typename T, typename U>
void pQueue<T,U>::dequeue()
{
    nodeq<T,U> *ptr = head;
    head = head->prevLink();
    delete ptr;
    --mySize;
}

template<typename T, typename U>
void pQueue<T,U>::nukem()
{
    for(nodeq<T,U> *ptr = head; head; ptr = head)
    {
        head = head->prevLink();
        delete ptr;
    }
    head = tail = NULL;
    mySize = 0;
}

template<typename T, typename U>
void pQueue<T,U>::copy(const pQueue<T,U>&other)
{
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    nodeq<T,U> *ptr = head = tail = other.head;
    for(; ptr; ptr = ptr->prevLink())
    {
        tail = new nodeq<T,U>(ptr->prevLink());
        tail->prevLink()->nextLink() = tail;
        tail = tail->prevLink();
    }
}

template<typename A, typename B>
ostream& operator<<(ostream &out, const pQueue<A,B> &pQ)
{
    for(nodeq<A,B> *ptr = pQ.head; ptr; ptr = ptr->prev)
        out<<*ptr<<" ";
    return out;
}

template<typename A, typename B>
istream& operator>>(istream &in,  pQueue<A,B> &pQ)
{
    nodeq<A,B> newnodeq;
    while(in>>newnodeq)
        pQ.enqueue(newnodeq.theData(),newnodeq.thePriority());
    return in;
}

#endif // PRIORITYQUEUE
