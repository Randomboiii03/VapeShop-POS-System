#include "headers.h"

using namespace std;

int generateDeveloperPin()
{
    time_t now = time(nullptr);
    tm *timeinfo = localtime(&now); // Get current date

    int year = timeinfo->tm_year + 1900; // Get current year
    int month = timeinfo->tm_mon + 1;    // Get current month
    int day = timeinfo->tm_mday;         // Get current day

    stringstream ss;
    ss << year;

    string lastTwoDigits = ss.str().substr(2); // Get last two digit of year
    ss.str("");

    ss << lastTwoDigits << month << day; // Compile current date

    int currenDate = stoi(ss.str());

    bitset<5> binaryNumber(day); // Convert day to binary

    int binaryDay = stoi(binaryNumber.to_string()); // Convert binaryNumber > string > integer

    int devPinCode = currenDate + binaryDay; // Add currentDate to binaryDay to get the devPinCode

    return devPinCode;
}