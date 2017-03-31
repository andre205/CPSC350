#include <iostream>
#include "GenStack.h"
#include "a3.h"
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	a3 a;

	//Check if there is only one command line argument
	if(argc == 2)
	{
		//See if the argument is a file. If so, run the application
		if(a.setFile(argv[1]))
		{
			while(true)
			{
				cout << "----------" << endl;
				a.populateStack();
				//a.printResult(); //for testing
				cout << "----------" << endl;

				cout << "Enter another file name to process another file or type Q to quit: ";

				//take input - quit or process another
				string i;
				getline(cin, i);
				if(i == "Q")
				{
					cout << "Quitting" << endl;
					break;
				}

				else
				{
					//if the text entered is a file, reset the stack and process the new file
					if(a.setFile(i))
					{
						a.resetStack();
						//continue on to populateStack again						
					}
					else
					{
						//they didnt enter a file name
						cout << "Error loading file. Exiting Application." << endl;
						break;
					}
				}
			}
		}

		else
		{
			//they didnt enter a file name (setFile() failed)
			cout << "Error loading file. Exiting Application." << endl;
		}
	}

	//If user forgets a command line argument or uses more than one - close the application
	else
		cout << "Please give a file name in the command line. Exiting Application" << endl;

	return 0;
}