
#ifndef GENLIST_H
#define GENLIST_H

#include "ListInterface.h"
#include "ListNode.h"
#include <iostream>
#include <exception>
using namespace std;

template<class T>
class GenList : public ListInterface<T> {
private:
    ListNode<T> *head;
    ListNode<T> *tail;
    unsigned int size;
public:
    GenList(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    ~GenList(){
        ListNode<T> *node = head;
        ListNode<T> *nodeToDelete = head;
        while (node != NULL){
            nodeToDelete = node->next;
            delete node;
            node = nodeToDelete;
        }
    }
    void append(T data){
        ListNode<T> *node = new ListNode<T>(data);

        if(isEmpty()){
            head = node;

        }
        else{
            node->prev = tail;
            tail->next = node;
        }
        tail = node;
        ++size;
    }

    void prepend(T data){
        ListNode<T> * node = new ListNode<T>(data);

        if(isEmpty()){
            tail = node;
        }
        else{
            //it's not empty
            node->next = head;
            head->prev = node;
        }
        head = node;
        ++size;
    }
    bool insertAfter(T data, int index){
        if(index >= size){
            return false;
        }
        int location = 0;
        ListNode<T>* current = head;
        while(current != NULL){
            if(location == index){
                break;
            }
            current = current->next;
            location++;
        }
        ListNode<T>* newNode = new ListNode<T>(data);
        if(index == size - 1){ //end of list insertion
            current->next = newNode;
            newNode->prev = current;
        }
        else{
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
        }
        return true;
    }
    T remove(){
        if(isEmpty()){
            return NULL;
        }

        ListNode<T> *tempnode = head;
        if(head->next == NULL){
            tail = NULL;
        }
        else{
            head->next->prev = NULL;
        }
        head = head->next;
        tempnode->next = NULL;
        T retdata = tempnode->data;
        --size;

        return retdata;
    }

    T search(T data){
        T pos = NULL;
        ListNode<T> *curr = head;

        while(curr != NULL){
            ++pos;
            if(curr->data == data)
                break;

            curr = curr->next;
        }

        if(curr == NULL)
            pos = NULL;

        return pos;
    }

    bool isEmpty(){
        return (size == 0);
    }

    int getLength(){
        return size;
    }

    T getFront(){
        if(head == NULL){
            return NULL;
        }
        else{
            return head->data;
        }
    }

};

#endif
