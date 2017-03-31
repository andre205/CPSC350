#include "Queue.h"
#include <string>

using namespace std;

class Processor
{
    public:
        Processor();
        ~Processor();

        bool readFile(string f);

    //private:
        Queue entryTimeQueue;
        Queue timeAtWindowQueue;
        int *windowArray;
        int *medianArray;
        DLL<int> *tempList;

        int waitTotal;
        int longestWait;
        double medianWait;
        double meanWait;
        int numWaitsOverTen;

        int studentTimeAtWindow;
        int lineType;
        int studentEntryTime;
        int numWindows;
        int numStudents;
        int totalStudents;
};
