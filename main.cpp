
#include <iostream>
#include <fstream>
#include "AdminOffice.h"

using namespace std;

int main(int argc, char **argv) {
    ifstream infile;
   if(argc < 2){
     cout << "Invalid Command line params" << endl;
     return 1;
   }

   infile.open(argv[1]);


    //print error if file cant be opened
    if(!infile.is_open()){
        cout << "Error failed to open file - " << argv[1] << endl;
        return 1;
    }

    //initialize empty queue
    GenQueue<Student*> arrivals;

    //set up variables for file reading
    int studentCount = 0;       //total number of students read from the file
    int windows;                //total number of windows, read from first line of file
    infile>>windows;            //read in first line to windows

    //error prevention for eof loop running one too many times
    int prevArrivalTime = 0;
    int prevStudentCount = 0;

    while(!infile.eof()){
        // initialize and read in the timestamp and how many students show up
        int time;
        int students;
        infile >> time;
        infile >> students;
        //use error prevention variables to prevent extra duplicate run
        if(prevArrivalTime == time && prevStudentCount == students){
            continue;
        }
        prevArrivalTime = time;
        prevStudentCount = students;

        //diagnostic print, not needed for submission
        cout << "Arrival Time: " << time << endl << "Students: " << students << endl;

        //add the number of students read in for this timestamp to the running total
        studentCount += students;

        //for however many students show up at this time stamp, read their window times and create objects with those data points. Add to arrivals queue
        for (int i = 0; i < students; i++) {
            int windowTime;
            infile>>windowTime;
            cout << "\tStudent: " << endl << " \t\twindowTime " << windowTime << endl;
            Student* stu = new Student(time, windowTime);
            arrivals.push(stu);
        }

    }

    //initialize office using the number of windows and number of students (they are used to initialize the dynamic arrays
    AdminOffice *office = new AdminOffice(windows, studentCount);

    //call the run function for the office, with the queue full of file data
    office->run(arrivals);

    //print all the math stats from the run
    office->printStats();

    delete office;
    return 0;


}
