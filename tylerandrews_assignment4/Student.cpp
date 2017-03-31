#include <iostream>
#include "Student.h"

using namespace std;

Student::Student()
{
}

Student::~Student(){};

Student::Student(int t, int e)
{
    timeAtWindow = t;
    entryTime = e;
    timeInQueue = 0;
}
