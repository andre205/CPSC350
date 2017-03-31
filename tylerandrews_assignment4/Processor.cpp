#include <iostream>
#include <fstream>
#include <string>
#include "Processor.h"

using namespace std;

Processor::Processor()
{
    waitTotal = 0;
    longestWait = 0;
    medianWait = 0;
    meanWait = 0;
    numWaitsOverTen = 0;

    studentTimeAtWindow = 0;
    lineType = 1;
    studentEntryTime = 0;
    numWindows = 0;
    numStudents = 0;
    totalStudents = 0;
}

Processor::~Processor()
{
    //delete windowArray;
}

bool Processor::readFile(string f)
{
    cout << "waitTotal: " << waitTotal << endl;

	ifstream inputfile;
	inputfile.open(f.c_str());
	string line;

	if (inputfile.is_open())
	{
        try
        {
            //First line number of windows
       		getline(inputfile,line);
       		numWindows = stoi(line);
        }

        catch (exception e)
        {
            cout << "ERROR" << endl;

            return false;
        }

        while (getline (inputfile,line))
        {
            cout << "NS" << numStudents << endl;
            cout << "got to the while" << endl;
            cout << lineType << endl;

            switch (lineType)
            {
                // CLOCK TICK
                case (1):
                {
                    cout << "got to first case" << endl;
                    try
                    {
                        //First line number of windows
                   		studentEntryTime = stoi(line);

                        ++lineType;
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: CLOCK TICK" << endl;

                        return false;
                    }

                    break;
                }

                // NUMBER OF STUDENTS
                case (2):
                {
                    try
                    {
                        //First line number of students
                   		numStudents = stoi(line);

                        cout << "NS: " << numStudents << endl;

                        for (int i = 0; i < numStudents; ++i)
                        {
                            getline (inputfile,line);

                            studentTimeAtWindow = stoi(line);

                            cout << "dygh? TAW: " << studentTimeAtWindow << endl;

                            // ADD WAIT TO TOTAL FOR STATS
                            waitTotal += studentTimeAtWindow;

                            totalStudents++;

                            if (studentTimeAtWindow > 10)
                            {
                                numWaitsOverTen++;
                            }

                            if (studentTimeAtWindow > longestWait)
                            {
                                longestWait = studentTimeAtWindow;
                            }

                            cout << "stud Ent " << studentEntryTime << endl;

                            entryTimeQueue.enqueue(studentEntryTime);
                            timeAtWindowQueue.enqueue(studentTimeAtWindow);
                        }

                        // NEXT LINE WILL BE CLOCK TICK
                        lineType = 1;
                    }

                    catch (exception e)
                    {
                        cout << "ERROR: NUM STUDENTS" << endl;

                        return false;
                    }

                    break;
                }

                default:break;
            }
        }
	}

    else
    {
        cout << "WHOEL THING DID NT WORK" << endl;

        return false;
    }

    windowArray = new int[numWindows];

    // MAKE ALL WINDOWS EMPTY
    for (int i = 0; i < numWindows; ++i)
    {
        windowArray[i] = 0;
    }

    cout << "waitTotal = " << waitTotal << endl;


    entryTimeQueue.queueList.insertBack(4);

    entryTimeQueue.queueList.printList();

//     OUTPUT
        // 1. The mean student wait time.
        // 2. The median student wait time.
        // 3. The longest student wait time.
        // 4. The number of students waiting over 10 minutes
        // 5. The mean window idle time
        // 6. The longest window idle time
        // 7. Number of windows idle for over 5 minutes.
//
//
    cout << "1 - mean wait time = " << float(waitTotal) / float(totalStudents) << endl;

    cout << "3 - longest wait time = " << longestWait << endl;

    cout << "4 - waits over 10 minutes = " << numWaitsOverTen << endl;


    return true;
}
