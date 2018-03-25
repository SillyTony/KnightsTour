#ifndef BaseStack
#define BaseStack

#include <node.h>

enum ERRORS{FULLS, EMPTYS};

template<typename T>
class Stack
{
    public:
        Stack();
        Stack(int s);
        ~Stack();
        Stack(const Stack<T>& other);
        Stack<T>& operator=(const Stack<T>& other);

        bool empty();
        bool full();
        void clear();
        void resize(int x);

        int size();
        int capacity();

        void push(const T& d);
        T& top();
        T& pop();

        Stack<T>& operator<<(const T &data);
        Stack<T>& operator>>(T &data);

        template<typename U>
        friend
        ostream& operator<<(ostream& out,  Stack<U>&y);

        template<typename U>
        friend
        istream& operator>>(istream& out,  Stack<U>&x);

    private:
        node<T>* root;
        int total, mySize;

        void nukem();
        void copy(const Stack<T>& other);
        void makeStack(const int &t);
};

template<typename T>
Stack<T>::Stack()
{
    makeStack(5);
}

template<typename T>
Stack<T>::Stack(int s)
{
    makeStack(s);
}

template<typename T>
Stack<T>::~Stack()
{
    nukem();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
    copy(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
bool Stack<T>::empty()
{
    return !root;
}

template<typename T>
bool Stack<T>::full()
{
    return mySize == total;
}

template<typename T>
void Stack<T>::clear()
{
    nukem();
}

template<typename T>
void Stack<T>::resize(int x)
{
    nukem();
    total = x;
}

template<typename T>
int Stack<T>::size()
{
    return mySize;
}

template<typename T>
int Stack<T>::capacity()
{
    return total;
}

template<typename T>
void Stack<T>::makeStack(const int& t)
{
    root = NULL;
    total = t;
    mySize = 0;
}

template<typename T>
void Stack<T>::nukem()
{
    for(node<T> *temp, *ptr = root;
        ptr;
        temp = ptr,
        ptr = ptr->theLink(),
        delete temp);
    mySize = 0;
    total = 0;
}

template<typename T>
void Stack<T>::copy(const Stack<T>& other)
{
    node<T> newRoot, *end = &newRoot;
    for(node<T>*ptr = other.root; ptr; ptr = ptr->theLink())
    {
        end->theLink() = new node<T>(*ptr);
        end = end->theLink();
    }
    root = newRoot.theLink();
}

template<typename T>
T& Stack<T>::pop()
{
    try
    {
        if(empty())
            throw EMPTYS;

        T data = root->theData();
        root = root->theLink();
        mySize--;
        return data;
    }
    catch(ERRORS)
    {
        cout<<"Stack is empty"<<endl;
    }
}

template<typename T>
void Stack<T>::push(const T &d)
{
    try
    {
        node<T>*temp, *newNode = new node<T>(d);

        if(full())
            throw FULLS;

        if(!root)
            root = newNode;
        else
        {
            temp = root;
            root = newNode;
            root->theLink() = temp;
        }
        mySize++;
    }
    catch(ERRORS)
    {
        cout<<"Stack is full"<<endl;
    }
}

template<typename T>
T& Stack<T>::top()
{
    return root->theData();
}

template<typename T>
Stack<T>& Stack<T>::operator<<(const T &data)
{
    push(data);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator>>(T &data)
{
    data = pop();
    return *this;
}

template<typename U>
ostream& operator<<(ostream& out,  Stack<U> &y)
{
    node<U>* temp = y.root;
    for(node<U>* ptr = temp; ptr; ptr = ptr->theLink())
        out<<y.pop()<<endl;
    return out;
}

template<typename U>
istream& operator>>(istream& in, Stack<U>&x)
{
    U data;
    int size;
    if(in == cin)
    {
        cout<<"Size of Stack = ";
        in>>size;
        x.total = size;
        cout<<"Fill the stack: ";
        while(in>>data)
        {
            x.push(data);
            if(x.mySize == x.total)
                break;
        }
    }
    return in;
}
#endif // BaseStack

