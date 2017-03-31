#include <iostream>
#include "Menu.h"
#include "Grid.h"
#include <string>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h> 
#include <time.h>
#include <unistd.h>


using namespace std;

int main(int argc, char** argv)
{
	Menu m1;
	Grid g1;
	int w;
	int h;
	int mode = 1;
	int speed = 1;
	bool stable = false;
	bool quit = false;
		
	m1.welcome();
	//DISPLAY INPUT OPTIONS, GET INPUT
	m1.showGenerationOptions();	
	m1.genChoice = m1.getGenerationChoice();
	
	//RANDOM GENERATION - GET SIZE AND DENSITY, GENERATE GRIDS ACCORDINGLY
	if (m1.genChoice == 1)
	{
		cout << "Enter a map size from 1 to 100.\n";
		g1.height = m1.getMapDimension();
		g1.width = g1.height;

		cout << "Enter a map density between 1 and 100 (0 is empty, 100 is full).\n";
		g1.density = m1.getMapDensity();
		g1.createGrids();
		g1.populateGrid(g1.density);
		cout << "Map generated.\n";
	}
	//INPUT FILE - READ FILE, GENEREATE GRIDS ACCORDINGLY
	else if (m1.genChoice == 2)
	{
		cout << "Please enter a map file name: ";
		g1.mapFileName = m1.getInputFileName();
		g1.generateGridFromFile();
		g1.width = g1.getWidthFromFile();
		g1.height = g1.getHeightFromFile();
		cout << "Map generated.\n";
	}

	//DISPLAY GAME MODES, SPEED OPTIONS, GET INPUT
	m1.showModeOptions();
	m1.modeChoice = m1.getModeChoice();
	m1.showSpeedOptions();
	m1.speedChoice = m1.getSpeedChoice();
	speed = m1.speedChoice;

	//MAIN LOOP (ACTUAL SIMULATION) - ONLY RUNS WHEN CONSECUTIVE GENS ARE DIFFERENT
	g1.gen = 0;

	cout << "Press Enter to start the simulation.\nThe simulation will not stop until it stablizes or reaches generation 10,000\n";
	cin.get();

	while(not stable and g1.gen < 10000 and not quit)
	{
		//1 SEC DELAY
		if (m1.speedChoice == 1)
		{
			g1.displayGen1(g1.height, g1.width);
			cout << '\n';
			sleep(1);
		}
		//WAITS FOR ENTER PRESS (OR QUIT)
		else if (m1.speedChoice == 2)
		{
			g1.displayGen1(g1.height, g1.width);
			cout << "\nPress Enter to see the next generation. (Type Q to quit): ";
			if (cin.get() == 'Q')
				quit = true;
		}
		//OUTPUTS DIRECTLY TO FILE
		else if (m1.speedChoice == 3)
		{
			g1.outputGen1();
			cout << "Generation " << g1.gen << " output to file.\n";
		}
	
		//FILLS GEN 2 WITH ALL -s
		g1.prepGen2();
		//g1.displayGen2(g1.height, g1.width);
		//APPLIES CELL CONTINUATION LOGIC FROM GEN1 TO GEN2
		g1.progressGens(m1.modeChoice);
		//CHECKS IF GEN2 = GEN1
		stable = g1.checkIfStable();
		//GEN1 IS PROGRESSED, GEN2 READY TO BE OVERWRITTED
		g1.overwriteGen1();
		//INCREMENT GENERATION COUNTER
		g1.gen++;
	}

	//FINAL OUTPUT
	if (stable)
	{
		cout << "Simulation stablized at generation " << g1.gen - 1 << "\nPlease press Enter to exit the application.\n";
		cin.get();
	}
	else if (quit)
		cout << "Quitting Application.\n";
	else
		cout << "Reached 10,000 generation limit - Exiting Application.\n";

	/* OUTPUT I USED FOR TESTING
	cout << "Map file name: " << g1.mapFileName;
	cout << "\nGEN MODE: " << m1.genChoice;
	cout << "\nMAP H: " << g1.height;
	cout << "\nMAP W: " << g1.width;
	cout << "\nMAP DEN: " << g1.density;
	cout << "\nBOUNDARY MODE: " << m1.modeChoice;
	cout << "\nSPEED MODE: " << m1.speedChoice;
	cout << "\nENDING GEN: " << g1.gen;
	*/

	//Clear arrays from memory
	g1.deleteGrids();

	return 0;
}