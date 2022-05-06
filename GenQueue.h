#ifndef GENQUEUE_H
#define GENQUEUE_H

#include "GenList.h"
using namespace std;

template<class T>
class GenQueue{
private:
    GenList<T> *myQueue;
public:
    GenQueue();
    void push(T d);
    T peek();
    T pop();
    bool isEmpty();
    int getSize();

};

template<class T>
GenQueue<T>::GenQueue(){
    myQueue = new GenList<T>();
}

template<class T>
void GenQueue<T>::push(T d){
    myQueue->append(d);
}

template<class T>
T GenQueue<T>::peek(){
    return myQueue->getFront();
}

template<class T>
T GenQueue<T>::pop(){
    return myQueue->remove();
}

template<class T>
bool GenQueue<T>::isEmpty(){
    return myQueue->isEmpty();
}

template<class T>
int GenQueue<T>::getSize(){
    return myQueue->getSize();
};

#endif
