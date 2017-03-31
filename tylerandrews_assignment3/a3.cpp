#include "a3.h"
#include "GenStack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


using namespace std;

//3 stacks for delim types
GenStack<char> s1(16); //for (
GenStack<char> s2(16); //for [
GenStack<char> s3(16); //for {
//3 stacks for line numbers of delims
GenStack<int> s4(16);
GenStack<int> s5(16);
GenStack<int> s6(16);

a3::a3(){};

a3::~a3(){};

//Check if file exists, then set filename member variable to it
int a3::setFile(string f)
{	
	ifstream filetest;	
	filetest.open(f.c_str());
	if (filetest.is_open())
	{
		cout << "File loaded." << endl;
		filetest.close();
		filename = f;
		return 1;
	}
	else
		return 0;	
};


void a3::populateStack()
{
	bool errorFree = true;
	int lines = 1;
	ifstream inputfile;	
	inputfile.open(filename.c_str());
	string line;
	int l;
	char c;
	if (inputfile.is_open())
	{	
		//read all lines from file
   		while(getline (inputfile,line) && errorFree)
   		{	
   			l = line.length();
   			//iterate through each line, check each char
   			for (int i = 0; i<l; ++i)
   			{
   				c = line[i];

   				//if opening delim - push it onto the stack
   				//if closing delim - pop top off of corresponding stack (delims cancel out)
   				//if closing delim BEFORE open delim - throw error
   				switch(c)
				{
					case('('):
					{
						s1.push(line[i]);
   						s4.push(lines);
						break;
					}
					case(')'):
					{
						if(s1.isEmpty())
						{
							cout << "Error: missing ( before line " << lines << endl;
							errorFree = false;
						}
						else
						{
							s1.pop();
	   						s4.pop();
	   					}
						break;
					}
					case('['):
					{
						s2.push(line[i]);
   						s5.push(lines);
						break;
					}
					case(']'):
					{
						if(s2.isEmpty())
						{
							cout << "Error: missing [ before line " << lines << endl;
							errorFree = false;
						}
						else
						{
							s2.pop();
	   						s5.pop();
	   					}
						break;
					}
					case('{'):
					{
						s3.push(line[i]);
   						s6.push(lines);
						break;
					}
					case('}'):
					{
						if(s3.isEmpty())
						{
							cout << "Error: missing { before line " << lines << endl;
							errorFree = false;
						}
						else
						{
							s3.pop();
	   						s6.pop();
	   					}
						break;
					}
					default:
						break;
				}
   			}   

   			//increment file line counter after each line	
   			++lines;		
	   	} 

	   	//if no closing delim errors were found while iterating through the file
	   	//the remaining opening delims on each stack DO NOT have closing counterparts
	   	//and are ERRORS
	   	if (errorFree)
	   	{
	   		int location;
			if(!s4.isEmpty())
			 	cout << "Error: missing ) after line " << s4.pop() << endl;
			else if (!s5.isEmpty())
				cout << "Error: missing ] after line " << s5.pop() << endl;
			else if (!s6.isEmpty())
				cout << "Error: missing } after line " << s6.pop() << endl;
	   	}
	   	
	   	//if no closing delim errors OR opening delim errors
	   	//the file is ERROR FREE
   		if (errorFree && s1.isEmpty() && s2.isEmpty() && s3.isEmpty())
			cout << "There were no errors found." << endl;

	}	

	//in the odd case that a bad file slipped through the setfile method
	else
	{
		cout << "Error opening file." <<endl;
	}

	inputfile.close();
};

//FOR TESTING
//prints stack and information regarding stacks
void a3::printResult()
{
	for (int i = 0; i < s1.top+1; ++i)
	{
		cout << s1.myArray[i] << "--";
	}

	cout << endl;

	for (int i = 0; i < s1.top+1; ++i)
	{
		cout << s2.myArray[i] << "--";
	}

	cout << "\nArray size: " << s1.max << endl;
	cout << "S1 elements: " << s1.top + 1 << endl;
	cout << "S2 elements: " << s2.top + 1 << endl;

};

//clear all stacks
void a3::resetStack()
{
	while(!s1.isEmpty())
		s1.pop();
	while(!s2.isEmpty())
		s2.pop();
	while(!s3.isEmpty())
		s4.pop();
	while(!s4.isEmpty())
		s4.pop();
	while(!s5.isEmpty())
		s5.pop();
	while(!s6.isEmpty())
		s6.pop();
};