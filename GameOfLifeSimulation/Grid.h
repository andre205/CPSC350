#include <string>

using namespace std;

class Grid
{
public:
	int height, width, density, gen;
	string mapFileName;
	char ** gen1;
	char ** gen2;

	Grid();
	~Grid();
	void createGrids();
	void deleteGrids();
	
	void generateGridFromFile();
	int getHeightFromFile();
	int getWidthFromFile();
	void populateGrid(int d);
	void prepGen2();
	void overwriteGen1();
	void progressGens(int m);
	void displayGen1(int h, int w);
	void displayGen2(int h, int w);
	void outputGen1();
	void outputGen2();
	bool checkIfStable();
};