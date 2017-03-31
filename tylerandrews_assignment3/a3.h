#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

class a3
{
public:
	string filename;
	int stackSize;
	
	a3();
	~a3();
	
	int setFile(string f);
	void populateStack();
	void printResult();
	void resetStack();
};