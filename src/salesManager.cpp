#include "globalUtils.h"

using namespace std;

void saveSales(const vector<Sales> &data)
{
    ofstream outputFile("database/sales.txt");

    if (outputFile.is_open())
    {
        for (const Sales &sales : data)
        {
            outputFile << sales.salesID << "," << sales.productID << "," << sales.price << "," << sales.quantity << "," << sales.paymentMode << "," << sales.transactionNum << "," << sales.currentTime << "\n";
        }

        outputFile.close();
    }
    else
    {
        cerr << "Error opening file for sales.\n";
    }
}

vector<Sales> loadSales(time_t currentDate)
{
    ifstream inputFile("database/sales.txt");

    vector<Sales> data;

    if (inputFile.is_open())
    {
        string line;

        while (getline(inputFile, line))
        {
            Sales sale;
            stringstream ss(line);
            string value;

            getline(ss, value, ',');
            sale.salesID = stoi(value);

            getline(ss, value, ',');
            sale.productID = stoi(value);

            getline(ss, value, ',');
            sale.price = stoi(value);

            getline(ss, value, ',');
            sale.quantity = stoi(value);

            getline(ss, sale.paymentMode, ',');

            getline(ss, sale.transactionNum, ',');

            getline(ss, sale.currentTime, ',');

            stringstream sss;
            tm *date = localtime(&currentDate);
            sss << put_time(date, "%Y-%m-%d");

            switch (saleFilterIndex)
            {
            case 0: // All
                data.push_back(sale);
                break;
            case 1: // By Day
            {
                string saleDate = splitString(sale.currentTime, ' ')[0];

                if (saleDate == sss.str())
                {
                    data.push_back(sale);
                }
            }
            break;
            case 2: // By Week
            {
                string saleDate = splitString(sale.currentTime, ' ')[0];

                for (string date : getWeekDates(currentDate))
                {
                    if (date == saleDate)
                    {
                        data.push_back(sale);
                        break;
                    }
                }
            }
            break;
            case 3: // By Month
            {
                string currentMonth = splitString(sss.str(), '-')[0] + "-" + splitString(sss.str(), '-')[1];

                string saleDate = splitString(sale.currentTime, ' ')[0];
                string saleMonth = splitString(saleDate, '-')[0] + "-" + splitString(saleDate, '-')[1];

                if (currentMonth == saleMonth)
                {
                    data.push_back(sale);
                }
            }
            break;
            case 4: // By Year
            {
                string currentYear = splitString(sss.str(), '-')[0];

                string saleDate = splitString(sale.currentTime, ' ')[0];
                string saleYear = splitString(saleDate, '-')[0];

                if (currentYear == saleYear)
                {
                    data.push_back(sale);
                }
            }
            break;
            }
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading sales.\n";
    }

    return data;
}

void deleteSales(int saleIndex, time_t currentDate)
{
    saleFilterIndex = 0;

    vector<Sales> sale = loadSales(currentDate);

    string temp = "Are you sure you want to delete this sale history? [Y/N]";
    centerText(temp, temp.length());

    while (true)
    {
        char ch = getch();

        if (ch == 'y')
        {
            for (int i = sale.size() - 1; i >= 0 ; i--)
            {
                if (sale[i].salesID == saleIndex)
                {
                    sale.erase(sale.begin() + i); // Delete history in sales
                }
            }

            saveSales(sale);

            temp = "Sale history deleted successfully!";
            centerText(temp, temp.length());

            Sleep(2000);
            salesDisplay(currentDate);
        }
        else if (ch == 'n')
        {
            salesDisplay(currentDate);
        }
    }
}