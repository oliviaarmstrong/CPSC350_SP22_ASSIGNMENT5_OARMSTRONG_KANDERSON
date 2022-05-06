#include "AdminOffice.h"

AdminOffice::AdminOffice(int wCount, int sCount){
    windowCount = wCount; //window count
    expectedStudents = sCount; //capacity
    windowarray = new Window[wCount]; //makes size of array the window count
    studentarray = new Student[sCount]; //makes size of array the student count
    studentCount = 0; //keeps track of how many students are in it, where the next one goes
    timeStamp = 0; //current time/tick
}
AdminOffice::AdminOffice(){
    windowarray = NULL;
    studentarray = NULL;
    windowCount = 0;
    expectedStudents = 0;
    studentCount = 0;
    timeStamp = 0;
}


void AdminOffice::run(GenQueue<Student*> arrivals){

    //initialize queue to hold students that are transitioning from arrivals (the array of all students scheduled to show up from the file) to a window to get help
    GenQueue<Student*> waitingForWindow;

    //while there are either students still waiting for windows or in arrivals, or at least one window still has a student
    while(!waitingForWindow.isEmpty() || !arrivals.isEmpty() || windowsStillOccupied()){

        //loop through all windows, and if a window is occupied, either remove student if they're finished (window time == 0) or decrement window time
        for(int i = 0; i < windowCount; i++){
            //if window has student
            if(windowarray[i].getOccupied() == true){
                //if student's window time has reached 0 kick them off window
                if(windowarray[i].getUser()->getWindowTime() == 0){
                    //moves them to student array when done at window, so that we still have their data for calculations at the end
                    Student *curr = windowarray[i].getUser();

                    //call function to clear out the user(student) variable for the window object
                    windowarray[i].studentFinished();

                    //call the admin office method to add the student to the array
                    addStudentRecord(*curr);
                }

                else{
                    //decrement by 1 on student's window time (counts the tick for that student while they're at the window)
                    windowarray[i].getUser()->tickTimeAtWindow();
                }
            }
        }

        /* LOOP BELOW:
        get all students from arrivals queue that should walk into the room on this timestamp
        move them from arrivals to waiting for window queue (in line for next open window)
        checking if timestamp of student matches time, only put on queue if time matches */

        Student* stu = arrivals.peek(); //get data from front of queue
        while(stu != NULL){
            //if the student should "arrive" on this time stamp, move them from arrivals to waiting for window
            if(stu->getArrivalTime() == timeStamp){
                waitingForWindow.push(arrivals.pop());
            }
            else{
                break;  //if they don't have the matching timestamp then there are no more people to add - break the loop
            }
            //peek the next thing on the queue to prep for next loop run
            stu = arrivals.peek();
        }

        //if there are open windows and people waiting in line to get to a window, move them to windows, until either no people left or all windows full
        while(!allWindowsOccupied() && !waitingForWindow.isEmpty()){
            //loop through all windows to find next empty one (in order of array) and fill it if there is a student waiting
            for(int i = 0; i < windowCount; i++){
                if(windowarray[i].getOccupied() == false){
                    //in case we fill windows in one iteration of the while loop, this will continue instead of trying to access the empty queue
                    if(waitingForWindow.isEmpty()){
                        continue;
                    }
                    //move student from waiting for window to empty window found
                    windowarray[i].studentArrives(waitingForWindow.pop());
                    //calculate wait time for the student
                    windowarray[i].getUser()->setWaitTime(timeStamp - windowarray[i].getUser()->getArrivalTime());
                }
            }
        }


        //loop through list of windows (array) if window is empty add one to idle time
        for(int i = 0; i < windowCount; i++){
            //check if occupied, unoccupied windows get idle time incremented
            if(windowarray[i].getOccupied() == false){
                windowarray[i].incrementIdle();
            }
        }
        //increment timestamp
        timeStamp++;
    }
}
//moving to final array for data purposes
void AdminOffice::addStudentRecord(Student stu){
    studentarray[studentCount] = stu; //passing data in, saving it to array, student count keeps count how many students are added
    studentCount++;
}

int AdminOffice::getWindowCount(){
    return windowCount;
}

bool AdminOffice::allWindowsOccupied(){
    bool full = true;
    for(int i = 0; i < windowCount; i++){
        if(windowarray[i].getOccupied() == false){
            full = false;
        }
    }
    return full;
}

bool AdminOffice::windowsStillOccupied(){
    bool atLeastOneWindowHasStudent = false;
    for(int i = 0; i < windowCount; i++){
        if(windowarray[i].getOccupied() == true){
            atLeastOneWindowHasStudent = true;
        }
    }
    return atLeastOneWindowHasStudent;
}

int AdminOffice::getStudentCount(){
    return expectedStudents;
}

//smallest to largest, sorting algorithm
void AdminOffice::sortStudentsByWait(){
    for(int i = 0; i < expectedStudents; i++){
        int smallestIndex = i;
        for(int j = i + 1; j < expectedStudents; j++){
            if(studentarray[j].getWaitTime() < studentarray[smallestIndex].getWaitTime()){
                smallestIndex = j;
            }
        }
        Student stu = studentarray[i];
        studentarray[i] = studentarray[smallestIndex];
        studentarray[smallestIndex] = stu;
    }
}

void AdminOffice::sortWindowsByIdle(){
    for(int i = 0; i < windowCount; i++){
        int smallestIndex = i;
        for(int j = i + 1; j < windowCount; j++){
            if(windowarray[j].getIdle() < windowarray[smallestIndex].getIdle()){
                smallestIndex = j;
            }
        }
        Window win = windowarray[i];
        windowarray[i] = windowarray[smallestIndex];
        windowarray[smallestIndex] = win;
    }
}

double AdminOffice::meanStudentWait(){
    double sum = 0;
    for(int i = 0; i < expectedStudents; i++){
        sum += studentarray[i].getWaitTime();
    }
    return sum / expectedStudents;
}

double AdminOffice::getMedianWait(){
    if(expectedStudents % 2 == 0){ //even number of students
        int leftMid = (expectedStudents / 2) - 1;
        int rightMid = expectedStudents / 2;
        double median = (studentarray[leftMid].getWaitTime() + studentarray[rightMid].getWaitTime()) / 2.0;
        return median;
    }
    else{
        int middle = expectedStudents / 2;
        return studentarray[middle].getWaitTime();
    }
}

// counts students wait time over 10 min
int AdminOffice::tallyWaitOver10(){
    int count = 0;
    for(int i = 0; i < expectedStudents; i++){
        if(studentarray[i].getWaitTime() >= 10){
            count++;
        }
    }
    return count;
}

//returns longest wait time
int AdminOffice::getLongestWait(){
    int longest = studentarray[0].getWaitTime();
    for(int i = 0; i < expectedStudents; i++){
        if(studentarray[i].getWaitTime() > longest){
            longest = studentarray[i].getWaitTime();
        }
    }
    return longest;
}

double AdminOffice::meanWindowIdleTime(){
    double sum = 0;
    for(int i = 0; i < windowCount; i++){
        sum += windowarray[i].getIdle();
    }
    return sum / windowCount;
}

int AdminOffice::longestIdleTime(){
    int longest = windowarray[0].getIdle();
    for(int i = 0; i < windowCount; i++){
        if(windowarray[i].getIdle() > longest){
            longest = windowarray[i].getIdle();
        }
    }
    return longest;
}

int AdminOffice::countWindowsIdleOver5(){
    int count = 0;
    for(int i = 0; i < windowCount; i++){
        if(windowarray[i].getIdle() >= 5){
            count++;
        }
    }
    return count;
}

void AdminOffice::printStats(){
    sortStudentsByWait();
    sortWindowsByIdle();

    cout << "Student Wait Time Stats:" << endl;
    cout << "\tMean Wait Time: " << meanStudentWait() << endl;
    cout << "\tMedian Wait Time: " << getMedianWait() << endl;
    cout << "\tLongest Wait Time: " << getLongestWait() << endl;
    cout << "\tNumber of Wait Times Over 10 Minutes: " << getLongestWait()<< endl << endl;

    cout << "Window Idle Time Statistics: " << endl;
    cout << "\tMean Idle Time: " << meanWindowIdleTime() << endl;
    cout << "\tLongest Idle Time: " << longestIdleTime() << endl;
    cout << "\tNumber of Idle Times Over 5 Minutes: " << countWindowsIdleOver5()<< endl;
}
