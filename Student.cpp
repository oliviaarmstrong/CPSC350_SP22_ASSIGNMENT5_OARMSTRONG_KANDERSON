#include "Student.h"

Student::Student(int arrive, int window){
    arrivalTime = arrive; //from text file, time they show up
    windowTime = window; //how long they need at window
    waitTime = 0; //calculated as diff between arrival time and actual timestamp when added to a window
}
Student::Student(){
    arrivalTime = -1;
    windowTime = -1;
    waitTime = 0;
}

//set the wait time (replaces old wait time, does NOT add)
void Student::setWaitTime(int wait){
    waitTime = wait;
}

//return arrival time
int Student::getArrivalTime(){
    return arrivalTime;
}

//return window time
int Student::getWindowTime(){
    return windowTime;
}

//return wait time
int Student::getWaitTime(){
    return waitTime;
}

//called to decrement time at a window so student can be removed when window time == 0
void Student::tickTimeAtWindow(){
    windowTime--;
}
