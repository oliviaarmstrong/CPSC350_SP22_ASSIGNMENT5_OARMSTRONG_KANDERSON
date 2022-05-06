
#ifndef AdminOffice_h
#define AdminOffice_h

#include <stdio.h>
#include "Student.h"
#include "Window.h"
#include "GenQueue.h"

class AdminOffice{
private:
    Window* windowarray; //read in from file
    Student* studentarray; //when a student is done at a window and leaves, saved to this dynamic array
    int windowCount; //count of windows
    int expectedStudents; //number of students expected/capacity
    int studentCount; //count of students
    int timeStamp; //current time/tick
public:
    AdminOffice(int wCount, int sCount);
    AdminOffice();

    //While loop that controls interaction of students, windows, time
    void run(GenQueue<Student*> arrivals);

    //Keeps track of students that are done with run process for stats purposes
    void addStudentRecord(Student stu);

    //Number of windows
    int getWindowCount();

    //True or false whether a whether all the windows are occupied
    bool allWindowsOccupied();

    //Whether a window is occupied
    bool windowsStillOccupied();

    //Student count
    int getStudentCount();

    //Smallest to largest, sorting algorithm, c++ selection sort
    void sortStudentsByWait();

    //Sorting algorithm
    void sortWindowsByIdle();

    double meanStudentWait();

    double getMedianWait();

    // counts students wait time over 10 min
    int tallyWaitOver10();

    //returns longest wait time
    int getLongestWait();

    double meanWindowIdleTime();

    int longestIdleTime();

    int countWindowsIdleOver5();

    void printStats();


};

#endif 
