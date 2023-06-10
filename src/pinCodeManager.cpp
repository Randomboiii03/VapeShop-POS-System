#include "globalUtils.h"

using namespace std;

// Get PIN code of admin
string getPinCode()
{
    ifstream inputFile("database/pinCode.txt"); // Open the input file
    string pinCode;

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

// Change PIN code of admin
void changePinCode(string newPinCode)
{
    ofstream outputFile("database/pinCode.txt");

    admin[0].pinCode = newPinCode;

    if (outputFile.is_open())
    {
        outputFile << newPinCode; // Write the new PIN code to the file
        outputFile.close();       // Close the file
    }
    else
    {
        cerr << "Failed to change PIN code." << endl;
    }
}
