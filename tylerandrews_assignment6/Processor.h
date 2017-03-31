#include <iostream>
#include <time.h>
#include <math.h>  
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

class Processor
{
    protected:

    public:
        int numDoubles;

        double* arr_quick;
        double* arr_insert;
        double* arr_gnome;

        Processor();
        ~Processor();

        bool readFromFile(string fn);
        void writeToFile();

        int checkInput(int l, int u, string m);

        void sortAll();

        void quickSort(double arr[], int left, int right);
        void swap(double arr[], int index1, int index2);

        void insertSort(double arr[], int marker);

        void gnomeSort(double array[], int size);

        void generateRandoms(int num, string op);
};
