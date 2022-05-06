#include "Window.h"

Window::Window(){
    idle = 0;
    occupied = false;
    stu = NULL;
}

//add 1 to idle time
void Window::incrementIdle(){
    if(!occupied){ //extra guard to not add idle time to occupied windows
        idle++;
    }
}

//get the idle time
int Window::getIdle(){
    return idle;
}

//get the bool occupied
bool Window::getOccupied(){
  return occupied;
}

//clear out a student from the window, reset everythign and return the student pointer
Student* Window::studentFinished(){
    Student *temp = stu;
    stu = NULL;
    occupied = false;
    return temp;
}

//put student at the window, update variables
void Window::studentArrives(Student* stu){
    occupied = true;
    this->stu = stu;
}

//return the student without removing
Student* Window::getUser(){
    return stu;
}
