#include "globalUtils.h"

using namespace std;

int getMaxLengthSales(const vector<Sales> &data, int columnIndex, string headerName)
{
    int maxLength = 0;
    int salesID = 0;
    float pricePurchase = 0;

    // Check for the datas width
    for (const auto &sale : data)
    {
        if (salesID != sale.salesID)
        {
            switch (columnIndex)
            {
            case 0:
                maxLength = max(maxLength, static_cast<int>(to_string(salesID).length()));
                break;
            case 1:
                maxLength = max(maxLength, static_cast<int>(splitString(sale.currentTime, ' ')[0].length()));
                break;
            case 2:
                maxLength = max(maxLength, static_cast<int>(sale.paymentMode.length()));
                break;
            case 3:
                maxLength = max(maxLength, static_cast<int>(maxLength, 10));
                break;
            case 4:
                pricePurchase += sale.price * sale.quantity;
                
                maxLength = max(maxLength, static_cast<int>(priceFormat(pricePurchase).length() + 2));

                salesID = sale.salesID;
                pricePurchase = sale.price * sale.quantity;
                break;
            default:
                // Invalid column index
                break;
            }
            break;
        }
        else
        {
            pricePurchase += sale.price * sale.quantity;
        }
    }

    maxLength = max(maxLength, static_cast<int>(headerName.length())); // Check for the header width

    return maxLength;
}

vector<string> getWeekDates(time_t currentDate)
{
    tm *date = localtime(&currentDate);
    int dayOfWeek = date->tm_wday;
    int secondsPerDay = 24 * 60 * 60; // Number of seconds in a day

    if (dayOfWeek != 0) // Adjust the start date if the current date is not a Sunday
    {
        // Calculate the number of seconds to subtract to get to the previous Sunday
        int secondsToSunday = dayOfWeek * secondsPerDay;

        // Subtract the seconds to get to the previous Sunday
        currentDate -= secondsToSunday;

        // Update the tm structure with the adjusted date
        date = localtime(&currentDate);
        dayOfWeek = date->tm_wday;
    }

    vector<string> weekDates;

    for (int i = 0; i < 7; i++) // Loop to get the dates for the entire week
    {
        stringstream ss;
        ss << put_time(date, "%Y-%m-%d"); // Create a string representation of the current date
        weekDates.push_back(ss.str());

        currentDate += secondsPerDay; // Increment the date by one day
        date = localtime(&currentDate);
    }

    return weekDates;
}

string getSalesTitle(time_t currentDate)
{
    stringstream ss;
    tm *date = localtime(&currentDate);
    ss << put_time(date, "%Y-%m-%d"); // Create a string representation of the current date

    vector<string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    vector<string> week = getWeekDates(currentDate);
    string temp;

    switch (saleFilterIndex)
    {
    case 0: // All
        temp = "All Sales";
        break;
    case 1: // By Day
        temp = "Sales for " + months[date->tm_mon] + " " + splitString(ss.str(), '-')[2] + ", " + splitString(ss.str(), '-')[0];
        break;
    case 2: // By Week
        temp = "Sales from " + months[stoi(splitString(week[0], '-')[1]) - 1] + " " + splitString(week[0], '-')[2] + ", " + splitString(week[0], '-')[0] + " to " + months[stoi(splitString(week[6], '-')[1]) - 1] + " " + splitString(week[6], '-')[2] + ", " + splitString(week[6], '-')[0];
        break;
    case 3: // By Month
        temp = "Sales for " + months[date->tm_mon] + " " + splitString(ss.str(), '-')[0];
        break;
    case 4: // By Year
        temp = "Sales for year - " + splitString(ss.str(), '-')[0];
        break;
    }

    return temp;
}