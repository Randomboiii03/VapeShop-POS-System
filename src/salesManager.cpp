#include "globalUtils.h"

using namespace std;

void saveSales(const vector<Sales> &data)
{
    ofstream outputFile("database/sales.txt");

    if (outputFile.is_open())
    {
        for (const Sales &sales : data)
        {
            outputFile << sales.productID << "," << sales.price << "," << sales.quantity << "," << sales.paymentMode << "," << sales.transactionNum << "," << sales.currentTime << "\n";
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
            sale.productID = stoi(value);

            getline(ss, value, ',');
            sale.price = stoi(value);

            getline(ss, value, ',');
            sale.quantity = stoi(value);

            getline(ss, sale.paymentMode, ',');

            getline(ss, sale.transactionNum, ',');

            getline(ss, sale.currentTime, ',');

            switch (saleFilterIndex)
            {
            case 0: // All
                data.push_back(sale);
                break;
            case 1: // By Day
            {
                stringstream sss;
                tm *date = localtime(&currentDate);
                sss << put_time(date, "%Y-%m-%d");

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
                stringstream sss;
                tm *date = localtime(&currentDate);
                sss << put_time(date, "%Y-%m-%d");

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
                stringstream sss;
                tm *date = localtime(&currentDate);
                sss << put_time(date, "%Y-%m-%d");

                string currentMonth = splitString(sss.str(), '-')[0] + "-" + splitString(sss.str(), '-')[1];

                string saleDate = splitString(sale.currentTime, ' ')[0];
                string saleMonth = splitString(saleDate, '-')[0] + "-" + splitString(saleDate, '-')[1];

                if (currentMonth == saleMonth)
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
    vector<Sales> saleFiltered = loadSales(currentDate);

    saleFilterIndex = 0;

    vector<Sales> sale = loadSales(currentDate); 

    string temp = "Are you sure you want to delete this sale history? [Y/N]";
    centerText(temp, temp.length());

    while (true)
    {
        char ch = getch();

        if (ch == 'y')
        {
            for (int i = 0; i < sale.size(); i++)
            {
                if (sale[i].currentTime == saleFiltered[saleIndex].currentTime && sale[i].productID == saleFiltered[saleIndex].productID)
                {
                    sale.erase(sale.begin() + saleIndex); // Delete history in sales
                    saveSales(sale);

                    break;
                }
            }

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