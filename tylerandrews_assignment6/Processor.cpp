#include "Processor.h"

using namespace std;

Processor::Processor(){};
Processor::~Processor(){};

bool Processor::readFromFile(string fn)
{
    ifstream f;
    string line;
    numDoubles = 0;

	f.open(fn.c_str());

    if (f.is_open())
    {
        try
        {
            // FIRST LINE IS TOTAL NUMBER OF DOUBLES
       		getline(f, line);

            if (line != "")
            {
                numDoubles = atoi(line.c_str());
            }
        }

        catch (exception e)
        {
            cout << "\nINCORRECT FILE FORMAT\n" << endl;
        }

        //CREATE ARRAYS OF SIZE numDoubles
        arr_quick = new double[numDoubles];
        arr_insert = new double[numDoubles];
        arr_gnome = new double[numDoubles];

        //NEXT numDoubles LINES ARE ALL DOUBLES FOR THE ARRAYS
        for (int j = 0; j < numDoubles; ++j)
        {
            getline(f, line);

            if (line != "")
            {
                //IF ERROR CREATING ARRAYS, QUIT.
                try
                {
                    arr_quick[j] = atof(line.c_str());
                    arr_insert[j] = atof(line.c_str());
                    arr_gnome[j] = atof(line.c_str());
                }   

                catch (exception e)
                {
                    cout << "\nINCORRECT FILE FORMAT\nEXITING APPLICATION\n" << endl;
                    return false;
                }
            }
        }
    }

    else
    {
        cout << "\nFILE NOT FOUND. NO DOUBLES LOADED." << endl;
        return false;
    }

    f.close();

    //NOTIFY USER, FILE LOADED
    cout << "FILE LOADED - " << fn << " - " << numDoubles << " doubles found.\n";

    return true;
}

//OUTPUT ALL ARRAYS TO FILES
void Processor::writeToFile()
{
    cout << "GENERATING FILES\n------------------\n";

    ofstream f;

    f.open("quick_out.txt");

    f << "Quick Sort on " << numDoubles << " doubles" << endl;

    for (int i = 1; i < numDoubles; ++i)
    {
        f << arr_quick[i] << endl;
    }

    f.close();

    f.open("insert_out.txt");

    f << "Insert Sort on " << numDoubles << " doubles" << endl;

    for (int i = 0; i < numDoubles; ++i)
    {
        f << arr_insert[i] << endl;
    }

    f.close();

    f.open("gnome_out.txt");

    f << "Gnome Sort on " << numDoubles << " doubles" << endl;

    for (int i = 0; i < numDoubles; ++i)
    {
        f << arr_gnome[i] << endl;
    }

    f.close();

    cout << "quick_out.txt CREATED\ninsert_out.txt CREATED\ngnome_out.txt CREATED\n------------------\n\n";

}

// RECEIVE INT INPUT BETWEEN PARAMETER BOUNDS AND DISPLAY MESSAGE ACCORDINGLY
int Processor::checkInput(int l, int u, string m)
{
    string answer;
    int answerInt;

    while (true)
    {
        cout << "\n" << m;

        answerInt = 0;
        answer = "";
        cin >> answer;

        // CHECK IF INPUT IS A NUMBER
        try
        {
            answerInt = atoi(answer.c_str());

            if (answerInt < u && answerInt > l)
            {

                return answerInt;
            }

            else
            {
                cout << "Please try again." << endl;
            }
        }

        catch (exception e)
        {
            cout << "Invalid input. Please enter an integer.";
        }
    }
}

//RUNS AND TIMES EACH ALGORITHM
void Processor::sortAll()
{
    cout << "SORTING\n------------------\n";
    clock_t c_begin = clock();
    clock_t c_end = clock();


    //QUICK SORT
    cout << "Quick sort initiated at time: " << c_begin << endl;;

    quickSort(arr_quick, 0, numDoubles);

    c_end = clock();

    cout << "Quick sort finished at time: " << c_end << endl;

    cout << "Quick Sort Complete. Run Time: " << (c_end - c_begin)/(CLOCKS_PER_SEC/1000) << "ms" << endl;

    cout << "----\n";
    //INSERTION SORT
    c_begin = clock();

    cout << "Insertion sort initiated at time: " << c_begin << endl;

    insertSort(arr_insert, numDoubles);

    c_end = clock();

    cout << "Insertion sort finished at time: " << c_end << endl;

    cout << "Insertion Sort Complete. Run Time: " << (c_end - c_begin)/(CLOCKS_PER_SEC/1000) << "ms" << endl;

    cout << "----\n";
    //GNOME SORT 
    c_begin = clock();

    cout << "Gnome sort initiated at time: " << c_begin << endl;

    gnomeSort(arr_gnome, numDoubles);

    c_end = clock();

    cout << "Gnome sort finished at time: " << c_end << endl;

    cout << "Gnome Sort Complete. Run Time: " << (c_end - c_begin)/(CLOCKS_PER_SEC/1000) << "ms" << endl;

    cout << "------------------\n";
}

void Processor::quickSort(double arr[], int left, int right)
{
    int i = left;
    int j = right;
    int pivot = arr[(left + right) / 2];        //pick the pivot point
    
    //I RAN INTO TROUBLE WITH PARTITION AS A SEPARATE METHOD SO I PUT IT HERE
    while(i <= j)
    {
        while(arr[i] < pivot)              //find elements on the left that belong on the right
        {            
            i++;
        }

        while(arr[j] > pivot)             //find elements on the right that belong on the left
        {   
            j--;
        }

        if(i <= j)                       //swap elements and move left/right indices
        {
            swap(arr, i, j);             //swap needs to be implemented (or use std swap)
            i++;
            j--;
        }
    }
    
    if(left < j)                //sort the left half 
    {
        quickSort(arr, left, j);
    }
        
    if(i < right)                   //sort the right half
    {
        quickSort(arr, i, right);
    }
}
        
//SIMPLE SWAP METHOD
void Processor::swap(double arr[], int index1, int index2)
{
    double temp;
    temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

//INSERTION SORT FROM CLASS
void Processor::insertSort(double arr[], int marker)
{
    int j;
    double temp;
        
    for (int i = 0; i < marker; i++)
    {
        j = i;
        
        while (j > 0 && arr[j] < arr[j-1])
        {
              temp = arr[j];
              arr[j] = arr[j-1];
              arr[j-1] = temp;
              j--;
        }
    }
}

//GNOME SORT FOUND ONLINE
//MODIFIED VERSION OF THE ONE FOUND HERE
//https://rosettacode.org/wiki/Sorting_algorithms/Gnome_sort#C.2B.2B
void Processor::gnomeSort(double array[], int size)
 {
    for (int i = 1; i < size;) 
    {
        if (array[i-1] <= array[i]) 
        {
            ++i;
        }

        else 
        {
           swap(array, i-1, i);
           --i;

           if (i == 0) 
           {
             i = 1;
           }
        }
    }
}

//FOR TESTING ONLY
//GENERATES A FILE WITH THE SPECIFIED NUMBER OF RANDOM DOUBLES
void Processor::generateRandoms(int num, string op)
{
    ofstream f;

    f.open(op.c_str());

    f << num << endl;

    for (int i = 0; i < num; ++i)
    {    
        f << rand() << endl;
    }
}