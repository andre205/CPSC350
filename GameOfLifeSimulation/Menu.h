#include <string>

using namespace std;

class Menu
{
public:
	int genChoice, modeChoice, speedChoice;
	Menu();
	~Menu();
	void welcome();
	void showGenerationOptions();
	int getGenerationChoice();
	int getMapDimension();
	string getInputFileName();
	int getMapDensity();
	void showModeOptions();
	int getModeChoice();
	void showSpeedOptions();
	int getSpeedChoice();
};