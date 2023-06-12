#include "globalUtils.h"

using namespace std;

int getMaxLengthSales(const vector<Sales> &data, const vector<Product> &data2, int columnIndex, string headerName)
{
    int maxLength = 0;

    // Check for the datas width
    for (const auto &sale : data)
    {
        for (const auto &product : data2)
        {
            if (sale.productID == product.productID)
            {
                string detail = product.productName + " - " + product.category;

                vector<string> currentTime = splitString(sale.currentTime, ' ');

                switch (columnIndex)
                {
                case 0:
                    maxLength = max(maxLength, static_cast<int>(to_string(data.size()).length()));
                    break;
                case 1:
                    maxLength = max(maxLength, static_cast<int>(currentTime[0].length()));
                    break;
                case 2:
                    maxLength = max(maxLength, static_cast<int>(detail.length()));
                    break;
                case 3:
                    maxLength = max(maxLength, static_cast<int>(to_string(sale.quantity).length()));
                    break;
                case 4:
                    maxLength = max(maxLength, static_cast<int>(priceFormat(product.price).length() - 2));
                    break;
                case 5:
                    maxLength = max(maxLength, static_cast<int>(priceFormat(product.price * sale.quantity).length() - 2));
                    break;
                case 6:
                    maxLength = max(maxLength, static_cast<int>(sale.paymentMode.length()));
                    break;
                case 7:
                    maxLength = max(maxLength, 10);
                    break;
                default:
                    // Invalid column index
                    break;
                }

                break;
            }
        }
    }

    maxLength = max(maxLength, static_cast<int>(headerName.length())); // Check for the header width

    return maxLength;
}

vector<string> getWeekDates()
{   
    auto now = chrono::system_clock::now();
    time_t currentDate = chrono::system_clock::to_time_t(now); // Get the current system time

    tm *date = std::localtime(&currentDate);
    int dayOfWeek = date->tm_wday;
    int secondsPerDay = 24 * 60 * 60; // Number of seconds in a day

    if (dayOfWeek != 0) // Adjust the start date if the current date is not a Sunday
    {
        // Calculate the number of seconds to subtract to get to the previous Sunday
        int secondsToSunday = dayOfWeek * secondsPerDay;

        // Subtract the seconds to get to the previous Sunday
        currentDate -= secondsToSunday;

        // Update the tm structure with the adjusted date
        date = std::localtime(&currentDate);
        dayOfWeek = date->tm_wday;
    }

    vector<string> weekDates;

    for (int i = 0; i < 7; i++) // Loop to get the dates for the entire week
    {
        stringstream ss;
        ss << std::put_time(date, "%Y-%m-%d"); // Create a string representation of the current date
        weekDates.push_back(ss.str());

        currentDate += secondsPerDay; // Increment the date by one day
        date = std::localtime(&currentDate);
    }

    return weekDates;
}