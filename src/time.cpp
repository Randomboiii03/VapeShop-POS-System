#include "headers.h"

using namespace std;

// Writes the expected time to a text file named "expecteTime.txt"
void saveExpectedTime(time_t expectedTime)
{
    ofstream outputFile("datas/expecteTime.txt");

    if (outputFile.is_open())
    {
        outputFile << expectedTime;
        outputFile.close();
    }
    else
    {
        cerr << "Failed to save expected time." << endl;
    }
}

// Reads the expected time from the file
time_t loadExpectedTime()
{
    ifstream inputFile("datas/expecteTime.txt");
    time_t expectedTime = 0;

    if (inputFile.is_open())
    {
        inputFile >> expectedTime;
        inputFile.close();
    }
    else
    {
        cerr << "Failed to load expected time." << endl;
    }

    return expectedTime;
}

// Calculates the expected time by adding one hour to the current time
time_t calculateExpectedTime()
{
    chrono::system_clock::time_point timePoint = chrono::system_clock::now();
    timePoint += chrono::hours(1);
    return chrono::system_clock::to_time_t(timePoint);
}

// Compare the current time and expected time
bool checkTimeMatches(time_t currentTime, time_t expectedTime)
{
    tm *tm1 = localtime(&currentTime);
    tm *tm2 = localtime(&expectedTime);

    return (tm1->tm_hour == tm2->tm_hour) && (tm1->tm_min == tm2->tm_min) && (tm1->tm_sec == tm2->tm_sec);
}