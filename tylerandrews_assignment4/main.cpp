/* Registrar's Office */

#include <iostream>
#include "Processor.h"

using namespace std;

int main(int argc, char** argv)
{
    Processor p;

    int time = 1;
    int openWindows = 0;

    bool running;

    // CHECK THAT THERE IS ONLY ONE COMMAND LINE ARGUMENT
	if (argc == 2)
	{
		// CHECK IF ARGUMENT IS A FILE; IF SO, RUN PROGRAM
		if (p.readFile(argv[1]))
		{
			cout << "WE DID IT HOORAY!!" << endl;

            while (true)
            {
                running = false;

                cout << "p.nW " << p.numWindows << endl;

                // IF ANY WINDOW IS OCCUPIED, CONTINUE RUNNING
                for (int i = 0; i < p.numWindows; ++i)
                {
                    if (p.windowArray[i] > 0)
                    {
                        cout << "put random shit" << endl;
                        running = true;
                    }
                }

                //cout << "p.entryTimeQueue.queueList.front->data " << p.entryTimeQueue.queueList.front->data << endl;

                // IF ANYONE IS STILL IN LINE, CONTINUE RUNNING
                if (!p.entryTimeQueue.isEmpty())
                {

                    running = true;
                }

                // MAIN PROGRAM
                if (running)
                {
                    cout << "DO YOU RUN???" << endl;

                    openWindows = 0;

                    // CHECK FOR OPEN WINDOWS
                    for (int i = 0; i < p.numWindows; ++i)
                    {
                        if (p.windowArray[i] < 1)
                        {
                            ++openWindows;
                        }
                    }

                    // // CHECK IF ANYONE IN LINE IS ALLOWED TO GO TO A WINDOW
                    // for (int i = 0; i < openWindows; ++i)
                    // {
                    //     if (p.entryTimeQueue.queueList.front->data <= time)
                    //     {
                    //         cout << "moved to window" << endl;
                    //     }
                    // }









                    for (int i = 0; i < p.numWindows; ++i)
                    {
                        if (p.windowArray[i] > 0)
                        {
                            p.windowArray[i]--;
                        }
                    }

                    ++time;
                }

                break;
            }
		}

		// INVALID FILE NAME
		else
		{
			cout << "\n*** Error loading file: File does not exist in current directory. ***\n\n<<< Exiting Program >>>\n" << endl;
		}
	}

	// ZERO OR MULTIPLE COMMAND LINE ARGUMENTS
	else
	{
		cout << "\n*** Please give a single file name in the command line. ***\n\n<<< Exiting Program >>>\n" << endl;
	}

	return 0;
}
