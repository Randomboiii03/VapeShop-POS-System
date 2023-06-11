#include "globalUtils.h"

using namespace std;

string getCurrentDateTime()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now); // Get the current system time

    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S"); // Convert the time to a string

    return ss.str();
}