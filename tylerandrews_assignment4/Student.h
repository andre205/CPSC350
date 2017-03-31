#include <iostream>

class Student
{
    public:
        Student();
        ~Student();
        Student(int t, int e);

    //private:
        int timeAtWindow;
        int entryTime;
        int timeInQueue;
};
