#include "headers.h"

using namespace std;

// Get PIN code
int getPinCode()
{
    ifstream inputFile("datas/pinCode.txt"); // Open the input file
    int pinCode;

    if (inputFile.is_open())
    {
        inputFile >> pinCode; // Read the PIN code from the file
        inputFile.close();    // Close the file
    }
    else
    {
        cerr << "Failed to get PIN code." << endl;
        // Handle the error or return a default value
    }

    return pinCode;
}

// Change PIN code
void changePinCode(int newPinCode)
{
    ofstream outputFile("datas/pinCode.txt");

    admin[0].pinCode = newPinCode;

    if (outputFile.is_open())
    {
        outputFile << newPinCode; // Write the new PIN code to the file
        outputFile.close();       // Close the file
        cout << "PIN code changed successfully." << endl;
    }
    else
    {
        cerr << "Failed to change PIN code." << endl;
    }
}
