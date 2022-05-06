
#ifndef LISTINTERFACE_H
#define LISTINTERFACE_H
template<class T>
class ListInterface{
  //virtual = 0, pure virtual function, cannot be implemented in base class, every class that inherits must have function done out and implemented
public:
    virtual void append(T data) = 0; //appends data to end of list
    virtual void prepend(T data) = 0; //prepends data to front of list
    virtual bool insertAfter(T data, int index) = 0; //inserts data after index
    virtual T remove() = 0; // removes data from list and returns it
    virtual bool isEmpty() = 0; //returns true if list has no items
    virtual int getLength() = 0; //returns number of items in the list

};



#endif /* ListInterface_h */
