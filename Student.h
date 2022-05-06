

#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

class Student{
private:
    int arrivalTime; //from text file, time they show up
    int windowTime; //how long they need at window
    int waitTime;  //calculated as diff between arrival time and actual timestamp when added to a window

public:
    Student(int arrive, int window);
    Student();

    //set the wait time (replaces old wait time, does NOT add)
    void setWaitTime(int wait);

    //return arrival time
    int getArrivalTime();

    //return window time
    int getWindowTime();

    //return wait time
    int getWaitTime();

    //called to decrement time at a window so student can be removed when window time == 0
    void tickTimeAtWindow();
};




#endif 
