//


#ifndef LISTNODE_H
#define LISTNODE_H

#include <stdio.h>

template <class T>
class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        ListNode *next;
        ListNode *prev;
        T data;
};

//implementation
template <class T>
ListNode<T>::ListNode(){}

template <class T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}


#endif /* ListNode_hpp */
