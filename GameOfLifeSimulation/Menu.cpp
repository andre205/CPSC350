#include "Menu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

int genChoice = 0;
int speedChoice = 0;
int modeChoice = 0;

Menu::Menu()
{
	//cout << "Created menu object";
};

Menu::~Menu()
{
	//cout << "Destroyed menu object";
};

void Menu::showGenerationOptions()
{
	cout << "Please select a map generation mode. (Type an integer response)\n";
	cout << "1. Random Generation\n2. Provide map file\n";
};

//ONLY ACCEPTS INT BETWEEN 0 AND 3
int Menu::getGenerationChoice()
{	
	int r = 0;
	string i;
	while (true)
	{
		getline(cin, i);
		stringstream ss(i);
		if(ss >> r)
			if(r<3 and r>0)
				break;
		cout <<  "Please enter a valid integer: ";
	}
	if (r == 1)
	{
		cout << "You have selected random generation mode.\n--------------------\n";
	} 
	else if (r == 2)
	{
		cout << "You have selected file input mode.\n--------------------\n";
	}
	return r;
};

//ONLY ACCEPTS INT 1-100 - CAN BE CHANGED TO ALLOW BIGGER GRIDS - SET TO 100 FOR NOW FOR SPACE
//2x2 causes problems so I took it out
int Menu::getMapDimension()
{
	int dim = 0;
	string i;
	while (true)
	{
		getline(cin, i);
		stringstream ss(i);
		if(ss >> dim)
			if (dim < 101 and dim != 2 and dim > 0)
				break;
		cout <<  "Please enter a valid integer: ";
	}
	return dim;   
};

//ACCEPTS INT 1-99
int Menu::getMapDensity()
{
	int den = 0;
	string i;
	while (true)
	{
		getline(cin, i);
		stringstream ss(i);
		if(ss >> den)
			if(den < 100 and den>0)
				break;
		cout <<  "Please enter a valid integer: ";

	}
	return den; 
};

//CHECKS IF FILE EXISTS THEN RETURNS NAME AS STRING
//ONLY ACCEPTS A FILE NAME THAT EXISTS AND HAS AN INTEGER IN THE FIRST TWO LINES
string Menu::getInputFileName()
{
	string i;
	while (true)
	{
		
		ifstream filetest;	
		getline(cin, i);
		filetest.open(i.c_str());
		//CHECK IF FIRST 2 LINES ARE INTEGERS, IF NOT, FILE IS INCORRECTLY FORMATTED
		if (filetest.is_open())
		{
			string l;
			int x;
			int y;
			getline (filetest,l);
	   		stringstream ss(l);
	   		getline (filetest,l);
	   		stringstream ss2(l);
	   		if (ss >> x and ss2 >> y)
   			{
   				filetest.close();
   				break;
   			}
   			else 
   			{
   				cout << "File is not the correct format, please try again: ";
   				filetest.close();
   			}
		}
		else
			cout << "File does not exist, please try again: ";
	}

	return i;
};

void Menu::showModeOptions()
{
	cout << "Please select a boundary mode. (Type an integer response)\n";
	cout << "1. Classic mode (Offscreen cells are empty).\n";
	cout << "2. Doughnut mode (Offscreen cells wrap around the map).\n";
	cout << "3. Mirror mode (Offscreen cells reflect back onto the map)\n";
};

//ACCEPTS INT 1-3
int Menu::getModeChoice()
{
	int r = 0;
	string i;
	while (true)
	{
		getline(cin, i);
		stringstream ss(i);
		if(ss >> r)
			if(r<4 and r>0)
				break;
		cout <<  "Please enter a valid integer: ";
	} 

	if (r == 1)
		cout << "You have selected Classic mode.\n--------------------\n";
	if (r == 2)
		cout << "You have selected Doughnut mode.\n--------------------\n";
	if (r==3) 
		cout << "You have selected Mirror mode.\n--------------------\n";

	return r;

};

//SAME FUNCTION DIFFERENT OUTPUTS
int Menu::getSpeedChoice()
{
	int r = 0;
	string i;
	while (true)
	{
		getline(cin, i);
		stringstream ss(i);
		if(ss >> r)
			if(r<4 and r>0)
				break;
		cout <<  "Please enter a valid integer: ";
	} 

	if (r == 1)
		cout << "There will be a brief pause between generations.\n--------------------\n";
	if (r == 2)
		cout << "You will need to press enter between generations.\n--------------------\n";
	if (r==3) 
		cout << "All generations will be output to tylerandrews.txt.\n--------------------\n";

	return r;

};
void Menu::showSpeedOptions()
{
	cout << "Please select a speed option for map generation progression. (Type an integer response)\n";
	cout << "1. Brief pause between generations.\n";
	cout << "2. Press the enter key between generations. (Recommended)\n";
	cout << "3. Output all generations to a file.\n";
};



void Menu::welcome()
{
	cout << "--------------------\n";
	cout << "      WELCOME TO   \n   THE GAME OF LIFE";
	cout << "\n--------------------\n";
};




/*
	void showGenerationOptions();
	int getGenerationChoice();

	int getMapLength();
	int getMapWidth();

	char* getInputFileName();
	float getMapDensity();

	void showModeOptions();
	int getModeChoice();

	void showSpeedOptions();
	int getSpeedChoice();

	char* getOutputFileName();
	*/