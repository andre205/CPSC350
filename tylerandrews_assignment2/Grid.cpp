#include "Grid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <algorithm>

using namespace std;

int height = 0;
int width = 0;
int density = 0;
int gen = 1;
string mapFileName = "";
char **gen1;
char **gen2;

Grid::Grid()
{
	//cout << "Created Grid object";
};

Grid::~Grid()
{
	//cout << "Destroyed Grid object";
};


//CREATE ARRAYS WITH GIVEN DIMENSIONS
void Grid::createGrids()
{
	gen1 = new char*[width];
	gen2 = new char*[width];

	for (int i = 0; i < width; ++i)
	{
		gen1[i] = new char[height];
		gen2[i] = new char[height];
	}
};

//REMOVE ARRAYS FROM MEMORY
void Grid::deleteGrids()
{
	for(int i = 0; i < width; ++i) 
	{
    	delete [] gen1[i];
    	delete [] gen2[i];    	
	}
	delete [] gen1;
	delete [] gen2;
};

//RETRIEVE THE ARRAY HEIGHT FROM THE FILE (FOR USE LATER)
int Grid::getHeightFromFile()
{
	//Open file, retrieve first line as int
	int h;
	ifstream inputfile;	
	inputfile.open(mapFileName.c_str());
	string line;
	if (inputfile.is_open())
	{	
   		getline (inputfile,line);
   		stringstream ss(line);
   		ss >> h;		
	}	

	//cout << "GHFF M: " << h;
	inputfile.close();
	return h;
};

//RETRIEVE THE ARRAY WIDTH FROM THE FILE (FOR USE LATER)
int Grid::getWidthFromFile()
{
	//Open file, retrieve second line as int
	int h;
	int w;
	ifstream inputfile;	
	inputfile.open(mapFileName.c_str());
	string line;
	if (inputfile.is_open())
	{	
   		getline (inputfile,line);
   		stringstream ss(line);
   		ss >> h;

   		getline (inputfile,line);
   		stringstream ss2(line);
   		ss2 >> w;		
	}	

	//cout << "GWFF M: " << w;
	inputfile.close();
	return w;
};

//CREATE GRID OBJECTS FROM FILE DATA
void Grid::generateGridFromFile()
{
	density = 0;
	int h;
	int w;
	ifstream inputfile;	
	inputfile.open(mapFileName.c_str());
	string line;
	if (inputfile.is_open())
	{	
		//First line height
   		getline (inputfile,line);
   		stringstream ss(line);
   		ss >> h;
   		//Second line width
   		getline (inputfile,line);
   		stringstream ss2(line);
   		ss2 >> w;
   		//Subsequent lines, actual grids
   		gen1 = new char*[w];
		gen2 = new char*[w];
		for (int i = 0; i < w; ++i)
		{
			gen1[i] = new char[h];
			gen2[i] = new char[h];
		}

		//Load map from file and display so user can see
   		for (int i = 0; i < h; ++i)
   		{
   			getline (inputfile,line);

   			for (int j = 0; j < w; ++j)
   			{	   			
   				gen1[j][i] = line[j];	

   				cout << gen1[j][i];   			
	   		}
	   		cout << '\n';
   		}
   		cout << '\n';
	}	
};

//GENERATE RANDOM NUMBER FROM 0 TO 1, IF LESS THAN DENSITY, CREATE CELL
void Grid::populateGrid(int d)
{
	//convert density to decimal value
	float den = (float)d / 100;

	double r1;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			r1 = (double)rand() / (double)(RAND_MAX);

			//within density, X, too high, empty
			if (r1 < den) 
				gen1[i][j] = 'X';
			else gen1[i][j] = '-';
		}
	}
};

//ITERATE THROUGH GEN1 GRID AND DISPLAY EACH CHAR
void Grid::displayGen1(int h, int w)
{
	cout << "Generation " << gen << "   (" << width << "x" << height << ")"<< '\n';

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{	   			
			cout << gen1[j][i];   			
   		}
   		cout << '\n';
	}
};

//FOR TESTING ONLY (NEVER SHOWN)
void Grid::displayGen2(int h, int w)
{
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			cout << gen2[j][i];
		}
		cout << '\n';
	}
	cout << '\n';
};

//FOR FILE OUTPUT, SAME CONCEPT AS DISPLAY
void Grid::outputGen1()
{
	ofstream outputfile;
	outputfile.open("tylerandrews.txt", std::ios_base::app);

	outputfile << "Generation " << gen << '\n';
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			outputfile << gen1[j][i];		
		}
		outputfile << '\n';	
	}
	outputfile << '\n';
	outputfile << '\n';
	outputfile.close();
};

//FILL GEN2 WITH -s TO BE OVERWRITTEN LATER
void Grid::prepGen2()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			gen2[j][i] = '-';
		}
	}
};

//COPY GEN2 TO GEN1
void Grid::overwriteGen1()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			gen1[j][i] = gen2[j][i];
		}
	}

};

//EVALUATES FALSE UNLESS EVERY ELEMENT OF GEN2 = GEN1
bool Grid::checkIfStable()
{

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if(gen1[x][y] != gen2[x][y])
				return false;
		}
	}

	return true;
};

//CELL PROGRESSION LOGIC
//ALL 3 MODES SHARE SAME LOGIC FOR INNER CELLS
//ONLY DIFFERENCE IS OUTER BORDER - m = 1,2,3 - classic, donut, mirror
void Grid::progressGens(int m)
{
	/*
	I visualized the 8 neighbors for each cell like this
	[1][2][3]
	[4][ ][5]   where the center cell is the one being checked
	[6][7][8]

	these neighbors are then totalled for the cell behavior in the next generation
	*/

	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	int n5 = 0;
	int n6 = 0;
	int n7 = 0;
	int n8 = 0;
	int ntot = 0;

	//CLASSIC MODE OUTER CELLS
	if (m == 1)
	{	
		//reference gen1[x][y] with [0][0] being the top left
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				//TOP ROW
				if (y == 0)
				{
					//LEFT CORNER
					if (x == 0)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[0][1] == 'X')
							n5 = 1;
						if (gen1[1][0] == 'X')
							n7 = 1;
						if (gen1[1][1] == 'X')
							n8 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';		
					}

					
					//RIGHT CORNER
					else if (x == width-1)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x-1][0] == 'X')
							n4 = 1;
						if (gen1[x-1][1] == 'X')
							n6 = 1;
						if (gen1[x][1] == 'X')
							n7 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';

					}
					
					
					//TOP MIDDLE
					else
					{
						if (x != 0 and x != width-1)
						{
							n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
							if (gen1[x-1][0] == 'X')
								n4 = 1;
							if (gen1[x+1][0] == 'X')
								n5 = 1;
							if (gen1[x-1][1] == 'X')
								n6 = 1;
							if (gen1[x][1] == 'X')
								n7 = 1;
							if (gen1[x+1][1] == 'X')
								n8 = 1;
							ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
							if (ntot < 2)
								gen2[x][y] = '-';
							else if (ntot == 2)
								gen2[x][y] = gen1[x][y];
							else if (ntot == 3)
								gen2[x][y] = 'X';
							else
								gen2[x][y] = '-';
						}

					}
									
				}

				//BOTTOM ROW
				if (y == height-1)
				{
					//LEFT CORNER
					if (x == 0)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x][y-1] == 'X')
							n2 = 1;
						if (gen1[x+1][y-1] == 'X')
							n3 = 1;
						if (gen1[x+1][y] == 'X')
							n5 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';		
					}
	
					//RIGHT CORNER
					else if (x == width-1)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x-1][y-1] == 'X')
							n1 = 1;
						if (gen1[x][y-1] == 'X')
							n2 = 1;
						if (gen1[x-1][y] == 'X')
							n4 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';
					}

					//BOTTOM MIDDLE
					else
					{
						if (x != 0 and x != width-1)
						{
							n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
							if (gen1[x-1][y-1] == 'X')
								n1 = 1;
							if (gen1[x][y-1] == 'X')
								n2 = 1;
							if (gen1[x+1][y-1] == 'X')
								n3 = 1;
							if (gen1[x-1][y] == 'X')
								n4 = 1;
							if (gen1[x+1][y] == 'X')
								n5 = 1;
							ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
							if (ntot < 2)
								gen2[x][y] = '-';
							else if (ntot == 2)
								gen2[x][y] = gen1[x][y];
							else if (ntot == 3)
								gen2[x][y] = 'X';
							else
								gen2[x][y] = '-';
						}

					}
				}

				//LEFT COL MIDDLE
				if (x == 0 and y != 0 and y != height-1)
				{
					n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
					if (gen1[x][y-1] == 'X')
						n2 = 1;
					if (gen1[x+1][y-1] == 'X')
						n3 = 1;
					if (gen1[x+1][y] == 'X')
						n5= 1;
					if (gen1[x][y+1] == 'X')
						n7 = 1;
					if (gen1[x+1][y+1] == 'X')
						n8 = 1;
					ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
					if (ntot < 2)
						gen2[x][y] = '-';
					else if (ntot == 2)
						gen2[x][y] = gen1[x][y];
					else if (ntot == 3)
						gen2[x][y] = 'X';
					else
						gen2[x][y] = '-';
				}

				//RIGHT COL MIDDLE
				if (x == width-1 and y != 0 and y != height-1)
				{
					n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
					if (gen1[x-1][y+1] == 'X')
						n1 = 1;
					if (gen1[x][y+1] == 'X')
						n2 = 1;
					if (gen1[x-1][y] == 'X')
						n4= 1;
					if (gen1[x-1][y-1] == 'X')
						n6 = 1;
					if (gen1[x][y-1] == 'X')
						n7 = 1;
					ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
					if (ntot < 2)
						gen2[x][y] = '-';
					else if (ntot == 2)
						gen2[x][y] = gen1[x][y];
					else if (ntot == 3)
						gen2[x][y] = 'X';
					else
						gen2[x][y] = '-';
				}

			}
		}
	}

	//DONUT MODE OUTER CELLS
	else if (m == 2)
	{	
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				//TOP ROW
				if (y == 0)
				{
					//LEFT CORNER
					if (x == 0)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[width-1][height-1] == 'X')
							n1 = 1;
						if (gen1[x][height-1] == 'X')
							n2 = 1;
						if (gen1[x+1][height-1] == 'X')
							n3 = 1;
						if (gen1[width-1][y] == 'X')
							n4 = 1;
						if (gen1[x+1][y] == 'X')
							n5 = 1;
						if (gen1[width-1][y] == 'X')
							n6 = 1;
						if (gen1[x][y+1] == 'X')
							n7 = 1;
						if (gen1[x+1][y+1] == 'X')
							n8 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';		
					}

					//RIGHT CORNER
					else if (x == width-1)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x-1][height-1] == 'X')
							n1 = 1;
						if (gen1[x][height-1] == 'X')
							n2 = 1;
						if (gen1[0][height-1] == 'X')
							n3 = 1;
						if (gen1[x-1][y] == 'X')
							n4 = 1;
						if (gen1[0][y] == 'X')
							n5 = 1;
						if (gen1[x-1][y+1] == 'X')
							n6 = 1;
						if (gen1[x][y+1] == 'X')
							n7 = 1;
						if (gen1[0][y+1] == 'X')
							n8 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';
					}
					
					//TOP MIDDLE
					else
					{
						if (x != 0 and x != width-1)
						{
							n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
							if (gen1[x-1][height-1] == 'X')
								n1 = 1;
							if (gen1[x][height-1] == 'X')
								n2 = 1;
							if (gen1[x+1][height-1] == 'X')
								n3 = 1;
							if (gen1[x-1][0] == 'X')
								n4 = 1;
							if (gen1[x+1][0] == 'X')
								n5 = 1;
							if (gen1[x-1][1] == 'X')
								n6 = 1;
							if (gen1[x][1] == 'X')
								n7 = 1;
							if (gen1[x+1][1] == 'X')
								n8 = 1;
							ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
							if (ntot < 2)
								gen2[x][y] = '-';
							else if (ntot == 2)
								gen2[x][y] = gen1[x][y];
							else if (ntot == 3)
								gen2[x][y] = 'X';
							else
								gen2[x][y] = '-';
						}

					}
									
				}

				//BOTTOM ROW
				if (y == height-1)
				{
					//LEFT CORNER
					if (x == 0)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[width-1][y-1] == 'X')
							n1 = 1;
						if (gen1[x][y-1] == 'X')
							n2 = 1;
						if (gen1[x+1][y-1] == 'X')
							n3 = 1;
						if (gen1[width-1][y] == 'X')
							n4 = 1;
						if (gen1[x+1][y] == 'X')
							n5 = 1;
						if (gen1[width-1][0] == 'X')
							n6 = 1;
						if (gen1[x][0] == 'X')
							n7 = 1;
						if (gen1[x+1][0] == 'X')
							n8 = 1;						
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';		
					}
	
					//RIGHT CORNER
					else if (x == width-1)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x-1][y-1] == 'X')
							n1 = 1;
						if (gen1[x][y-1] == 'X')
							n2 = 1;
						if (gen1[0][y-1] == 'X')
							n3 = 1;
						if (gen1[x-1][y] == 'X')
							n4 = 1;
						if (gen1[0][y] == 'X')
							n5 = 1;
						if (gen1[x-1][0] == 'X')
							n6 = 1;
						if (gen1[x][0] == 'X')
							n7 = 1;
						if (gen1[0][0] == 'X')
							n8 = 1;		
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';
					}

					//BOTTOM MIDDLE
					else
					{
						if (x != 0 and x != width-1)
						{
							n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
							if (gen1[x-1][y-1] == 'X')
								n1 = 1;
							if (gen1[x][y-1] == 'X')
								n2 = 1;
							if (gen1[x+1][y-1] == 'X')
								n3 = 1;
							if (gen1[x-1][y] == 'X')
								n4 = 1;
							if (gen1[x+1][y] == 'X')
								n5 = 1;
							if (gen1[x-1][0] == 'X')
								n6 = 1;
							if (gen1[x][0] == 'X')
								n7 = 1;
							if (gen1[x+1][0] == 'X')
								n8 = 1;	
							ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
							if (ntot < 2)
								gen2[x][y] = '-';
							else if (ntot == 2)
								gen2[x][y] = gen1[x][y];
							else if (ntot == 3)
								gen2[x][y] = 'X';
							else
								gen2[x][y] = '-';
						}

					}
				}

				//LEFT COL MIDDLE
				if (x == 0 and y != 0 and y != height-1)
				{
					n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
					if (gen1[width-1][y-1] == 'X')
						n1 = 1;
					if (gen1[x][y-1] == 'X')
						n2 = 1;
					if (gen1[x+1][y-1] == 'X')
						n3 = 1;
					if (gen1[width-1][y] == 'X')
						n4 = 1;
					if (gen1[x+1][y] == 'X')
						n5 = 1;
					if (gen1[width-1][y+1] == 'X')
						n6 = 1;
					if (gen1[x][y+1] == 'X')
						n7 = 1;
					if (gen1[x+1][y+1] == 'X')
						n8 = 1;	
					ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
					if (ntot < 2)
						gen2[x][y] = '-';
					else if (ntot == 2)
						gen2[x][y] = gen1[x][y];
					else if (ntot == 3)
						gen2[x][y] = 'X';
					else
						gen2[x][y] = '-';
				}

				//RIGHT COL MIDDLE
				if (x == width-1 and y != 0 and y != height-1)
				{
					n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
					if (gen1[x-1][y-1] == 'X')
						n1 = 1;
					if (gen1[x][y-1] == 'X')
						n2 = 1;
					if (gen1[0][y-1] == 'X')
						n3 = 1;
					if (gen1[x-1][y] == 'X')
						n4 = 1;
					if (gen1[0][y] == 'X')
						n5 = 1;
					if (gen1[x-1][y+1] == 'X')
						n6 = 1;
					if (gen1[x][y+1] == 'X')
						n7 = 1;
					if (gen1[0][y+1] == 'X')
						n8 = 1;	
					ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
					if (ntot < 2)
						gen2[x][y] = '-';
					else if (ntot == 2)
						gen2[x][y] = gen1[x][y];
					else if (ntot == 3)
						gen2[x][y] = 'X';
					else
						gen2[x][y] = '-';
				}

			}
		}
	}

	//MIRROR MODE OUTER CELLS
	else if (m == 3)
	{	
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				//TOP ROW
				if (y == 0)
				{
					//LEFT CORNER - If occupied counts as 3 neighbors (1, 2 , and 4)
					if (x == 0)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x][y] == 'X')
							n1 = 1;
						if (gen1[x][y] == 'X')
							n2 = 1;
						if (gen1[x+1][y] == 'X')
							n3 = 1;
						if (gen1[x][y] == 'X')
							n4 = 1;
						if (gen1[x+1][y] == 'X')
							n5 = 1;
						if (gen1[x][y+1] == 'X')
							n6 = 1;
						if (gen1[x][y+1] == 'X')
							n7 = 1;
						if (gen1[x+1][y+1] == 'X')
							n8 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';		
					}

					//RIGHT CORNER - 3 neighbors are 2, 3, 5
					else if (x == width-1)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x-1][y] == 'X')
							n1 = 1;
						if (gen1[x][y] == 'X')
							n2 = 1;
						if (gen1[x][y] == 'X')
							n3 = 1;
						if (gen1[x-1][y] == 'X')
							n4 = 1;
						if (gen1[x][y] == 'X')
							n5 = 1;
						if (gen1[x-1][y+1] == 'X')
							n6 = 1;
						if (gen1[x][y+1] == 'X')
							n7 = 1;
						if (gen1[x][y+1] == 'X')
							n8 = 1;
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';
					}
					
					//TOP MIDDLE - same behavior as donut except for 1, 2, 3 (upper neighbors)
					else
					{
						if (x != 0 and x != width-1)
						{
							n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
							if (gen1[x-1][y] == 'X')
								n1 = 1;
							if (gen1[x][y] == 'X')
								n2 = 1;
							if (gen1[x+1][y] == 'X')
								n3 = 1;
							if (gen1[x-1][y] == 'X')
								n4 = 1;
							if (gen1[x+1][y] == 'X')
								n5 = 1;
							if (gen1[x-1][y+1] == 'X')
								n6 = 1;
							if (gen1[x][y+1] == 'X')
								n7 = 1;
							if (gen1[x+1][y+1] == 'X')
								n8 = 1;
							ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
							if (ntot < 2)
								gen2[x][y] = '-';
							else if (ntot == 2)
								gen2[x][y] = gen1[x][y];
							else if (ntot == 3)
								gen2[x][y] = 'X';
							else
								gen2[x][y] = '-';
						}

					}			
				}

				//BOTTOM ROW
				if (y == height-1)
				{
					//LEFT CORNER - 3n are 4, 6, 7
					if (x == 0)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x][y-1] == 'X')
							n1 = 1;
						if (gen1[x][y-1] == 'X')
							n2 = 1;
						if (gen1[x+1][y-1] == 'X')
							n3 = 1;
						if (gen1[x][y] == 'X')
							n4 = 1;
						if (gen1[x+1][y] == 'X')
							n5 = 1;
						if (gen1[x][y] == 'X')
							n6 = 1;
						if (gen1[x][y] == 'X')
							n7 = 1;
						if (gen1[x+1][y] == 'X')
							n8 = 1;						
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';		
					}
	
					//RIGHT CORNER - 3n are 5, 7, 8
					else if (x == width-1)
					{
						n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
						if (gen1[x-1][y-1] == 'X')
							n1 = 1;
						if (gen1[x][y-1] == 'X')
							n2 = 1;
						if (gen1[x][y-1] == 'X')
							n3 = 1;
						if (gen1[x-1][y] == 'X')
							n4 = 1;
						if (gen1[x][y] == 'X')
							n5 = 1;
						if (gen1[x-1][y] == 'X')
							n6 = 1;
						if (gen1[x][y] == 'X')
							n7 = 1;
						if (gen1[x][y] == 'X')
							n8 = 1;		
						ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
						if (ntot < 2)
							gen2[x][y] = '-';
						else if (ntot == 2)
							gen2[x][y] = gen1[x][y];
						else if (ntot == 3)
							gen2[x][y] = 'X';
						else
							gen2[x][y] = '-';
					}

					//BOTTOM MIDDLE - same except for 6, 7, 8 (lower neighbors)
					else
					{
						if (x != 0 and x != width-1)
						{
							n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
							if (gen1[x-1][y-1] == 'X')
								n1 = 1;
							if (gen1[x][y-1] == 'X')
								n2 = 1;
							if (gen1[x+1][y-1] == 'X')
								n3 = 1;
							if (gen1[x-1][y] == 'X')
								n4 = 1;
							if (gen1[x+1][y] == 'X')
								n5 = 1;
							if (gen1[x-1][y] == 'X')
								n6 = 1;
							if (gen1[x][y] == 'X')
								n7 = 1;
							if (gen1[x+1][y] == 'X')
								n8 = 1;	
							ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
							if (ntot < 2)
								gen2[x][y] = '-';
							else if (ntot == 2)
								gen2[x][y] = gen1[x][y];
							else if (ntot == 3)
								gen2[x][y] = 'X';
							else
								gen2[x][y] = '-';
						}

					}
				}

				//LEFT COL MIDDLE
				if (x == 0 and y != 0 and y != height-1)
				{
					n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
					if (gen1[x][y-1] == 'X')
						n1 = 1;
					if (gen1[x][y-1] == 'X')
						n2 = 1;
					if (gen1[x+1][y-1] == 'X')
						n3 = 1;
					if (gen1[x][y] == 'X')
						n4 = 1;
					if (gen1[x+1][y] == 'X')
						n5 = 1;
					if (gen1[x][y+1] == 'X')
						n6 = 1;
					if (gen1[x][y+1] == 'X')
						n7 = 1;
					if (gen1[x+1][y+1] == 'X')
						n8 = 1;	
					ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
					if (ntot < 2)
						gen2[x][y] = '-';
					else if (ntot == 2)
						gen2[x][y] = gen1[x][y];
					else if (ntot == 3)
						gen2[x][y] = 'X';
					else
						gen2[x][y] = '-';
				}

				//RIGHT COL MIDDLE
				if (x == width-1 and y != 0 and y != height-1)
				{
					n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
					if (gen1[x-1][y-1] == 'X')
						n1 = 1;
					if (gen1[x][y-1] == 'X')
						n2 = 1;
					if (gen1[x][y-1] == 'X')
						n3 = 1;
					if (gen1[x-1][y] == 'X')
						n4 = 1;
					if (gen1[x][y] == 'X')
						n5 = 1;
					if (gen1[x-1][y+1] == 'X')
						n6 = 1;
					if (gen1[x][y+1] == 'X')
						n7 = 1;
					if (gen1[x][y+1] == 'X')
						n8 = 1;	
					ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
					if (ntot < 2)
						gen2[x][y] = '-';
					else if (ntot == 2)
						gen2[x][y] = gen1[x][y];
					else if (ntot == 3)
						gen2[x][y] = 'X';
					else
						gen2[x][y] = '-';
				}

			}
		}
	}

	//INNER CELLS (SAME FOR ALL MODES)
	for (int i = 1; i < height-2; ++i)
	{
		for (int j = 1; j < width-2; ++j)
		{
			n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0; n6 = 0; n7 = 0; n8 = 0; ntot = 0;
			if (gen1[j-1][i-1] == 'X')
				n1 = 1;
			if (gen1[j-1][i] == 'X')
				n2 = 1;
			if (gen1[j-1][i+1] == 'X')
				n3 = 1;
			if (gen1[j][i-1] == 'X')
				n4 = 1;
			if (gen1[j][i+1] == 'X')
				n5 = 1;
			if (gen1[j+1][i-1] == 'X')
				n6 = 1;
			if (gen1[j+1][i] == 'X')
				n7 = 1;
			if (gen1[j+1][i+1] == 'X')
				n8 = 1;
			ntot = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
			if (ntot < 2)
				gen2[j][i] = '-';
			else if (ntot == 2)
				gen2[j][i] = gen1[j][i];
			else if (ntot == 3)
				gen2[j][i] = 'X';
			else
				gen2[j][i] = '-';
		}
	}
};