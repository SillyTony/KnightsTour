#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;
template<typename T>
class node
{
    public:
        node();
        node(const T&);
        ~node();
        node(const node<T> &);
        node<T> operator=(const node<T> &);

        T& theData();
        node<T>*& theLink();
        void setLink(node<T>* ptr);
        void setData(const T& d);

        template<typename U>
        friend
        ostream& operator<<(ostream &, const node<U> &);

        template<typename U>
        friend
        istream& operator>>(istream &, node<U> &);

    private:
        T data;
        node<T> *next;

        void copy(const node<T> &);
        void nukem();
};

template<typename T>
node<T>::node()
{
    nukem();
}

template<typename T>
node<T>::node(const T &d)
{
    data = d;
    next = NULL;
}

template<typename T>
node<T>::~node()
{
    nukem();
}

template<typename T>
node<T>::node(const node<T> &other)
{
    copy(other);
}

template<typename T>
node<T> node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
T& node<T>::theData()
{
    return data;
}

template<typename T>
node<T>*& node<T>::theLink()
{
    return next;
}

template<typename T>
void node<T>::setLink(node<T>* ptr)
{
    next = ptr;
}

template<typename T>
void node<T>::setData(const T& d)
{
    data = d;
}

template<typename T>
void node<T>::copy(const node<T> &other)
{
    data = other.data;
    next = NULL;
}

template<typename T>
void node<T>::nukem()
{
    next = NULL;
    data = T();
}

template<typename U>
ostream& operator<<(ostream& out, const node<U>& object)
{
    out<<"("<<object.data<<") ";
    return out;
}

template<typename U>
istream& operator>>(istream& in, node<U>& object)
{
    U data;
    char junk;
    if(in == cin)
    {
        cout<<"Data: ";
        in>>data;
    }
    else
        in>>data>>junk;
    object.theData() = data;
    object.theLink() = NULL;
    return in;
}

#endif // NODE_H
