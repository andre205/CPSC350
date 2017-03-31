#include "Processor.h"
#include <string>

using namespace std;

int main (int argc, char** argv)
{
    //CHECK IF ONLY 1 COMMAND LINE INPUT
    if (argc == 2)
    {
        string inputfilename = argv[1];
        Processor p1;

        //CAN USE TO GENERATE A FILE WITH RANDOM NUMBERS IF NEEDED
        //p1.generateRandoms(50000, "input.txt");

        //IF FILE IS CORRECT FORMAT, SORT AND PROMPT
        if(p1.readFromFile(inputfilename))
        {
            p1.sortAll();

            cout << "Would you like to write the sorted arrays to files?\n1. Yes\n2. No";

            if (p1.checkInput(0,3,"Type 1 for Yes or 2 for No: ") == 1)
                p1.writeToFile();

            cout << "Exiting application\n";
        }

        else
        {
            cout << "\nExiting application\n";
        }
    }
    
    else
    {
        cout << "Incorrect terminal input. Please enter one file name as a command line argument.\nExiting Application.\n";
    }

    return 0;
}
