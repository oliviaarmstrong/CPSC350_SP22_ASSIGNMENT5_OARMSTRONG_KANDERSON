
#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include "Student.h"

class Window{
private:
    int idle; //running total for time window has been idle
    Student* stu;   //student that's currently at the window, NULL if empty.
    bool occupied;  //bool to track if window is occupied
public:
    Window();

    //add 1 to idle time
    void incrementIdle();

    //get the idle time
    int getIdle();

    //get the bool occupied
    bool getOccupied();

    //clear out a student from the window, reset everythign and return the student pointer
    Student* studentFinished();

    //put student at the window, update variables
    void studentArrives(Student* stu);

    //return the student without removing
    Student* getUser();
};

#endif
