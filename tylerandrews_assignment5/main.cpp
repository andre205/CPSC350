#include "Processor.h"

using namespace std;

int main (int argc, char** argv)
{
    Processor p1;
    Menu menu;

    p1.readFromFile();

    menu.welcome();

    p1.run();

    p1.writeToFile();

    // p1.addFaculty();
    //
    // cout << "-----------------" << endl;
    //
    // p1.addStudent();
    //
    // p1.printMasterStudent(p1.getMasterStudentRoot());
    //
    // p1.masterStudent.deleteNode(150);
    //
    // cout << endl << endl;
    //
    // p1.printMasterStudent(p1.getMasterStudentRoot());
    //
    // cout << endl << endl;
    //
    // //p1.displayStudentInfo(800);
    // //p1.displayStudentInfo(150);
    //
    // cout << "------------------------\n\n";
    //
    // p1.printMasterFaculty(p1.getMasterFacultyRoot());


    return 0;
}
