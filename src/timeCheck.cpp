#include "globalUtils.h"

using namespace std;

// Writes the expected time to a text file named "expecteTime.txt"
void saveExpectedTime(time_t expectedTime)
{
    ofstream outputFile("databaseFolder/expectedTime.txt");

    if (outputFile.is_open())
    {
        outputFile << expectedTime << " " << tries;
        outputFile.close();
    }
    else
    {
        cerr << "Failed to save expected time." << endl;
    }
}

// Reads the expected time from the file
ExpectedTimeData loadExpectedTime()
{
    ExpectedTimeData data;

    ifstream inputFile("databaseFolder/expectedTime.txt");

    if (inputFile.is_open())
    {
        inputFile >> data.expectedTime >> data.tries;
        inputFile.close();
    }
    else
    {
        cerr << "Failed to load expected time." << endl;
    }

    return data;
}

// Calculates the expected time by adding one hour to the current time
time_t calculateExpectedTime()
{
    chrono::system_clock::time_point timePoint = chrono::system_clock::now();
    timePoint += chrono::hours(1);
    return chrono::system_clock::to_time_t(timePoint);
}

// Compare the current time and expected time
void checkTime(time_t expectedTime)
{
    time_t currentTime = time(nullptr);

    if (currentTime >= expectedTime)
    {
        tries = 0;
        saveExpectedTime(currentTime);
    }
}