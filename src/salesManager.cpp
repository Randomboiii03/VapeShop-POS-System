#include "globalUtils.h"

using namespace std;

void saveSales(const vector<Sales> &data)
{
    ofstream outputFile("database/sales.txt", ios::app);

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
    vector<Sales> data;

    switch (saleFilterIndex)
    {
    case 0:
        data = loadAllSales();
        break;
    case 1:
        data = loadByDaySales(currentDate);
        break;
    case 2:
        data = loadByWeekSales(currentDate);
        break;
    case 3:
        data = loadByMonthSales(currentDate);
        break;
    case 4:
        data = loadByYearSales(currentDate);
        break;
    }

    return data;
}

vector<Sales> loadAllSales()
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

            data.push_back(sale);
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading sales.\n";
    }

    return data;
}

vector<Sales> loadByDaySales(time_t currentDate)
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

            stringstream sss;
            tm *date = localtime(&currentDate);
            sss << put_time(date, "%Y-%m-%d");

            string saleDate = splitString(sale.currentTime, ' ')[0];

            if (saleDate != sss.str())
            {
                continue;
            }

            data.push_back(sale);
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading sales.\n";
    }

    return data;
}

vector<Sales> loadByWeekSales(time_t currentDate)
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

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading sales.\n";
    }

    return data;
}

vector<Sales> loadByMonthSales(time_t currentDate)
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

            stringstream sss;
            tm *date = localtime(&currentDate);
            sss << put_time(date, "%Y-%m-%d");

            string currentMonth = splitString(sss.str(), '-')[0] + "-" + splitString(sss.str(), '-')[1];

            string saleDate = splitString(sale.currentTime, ' ')[0];
            string saleMonth = splitString(saleDate, '-')[0] + "-" + splitString(saleDate, '-')[1];

            if (currentMonth != saleMonth)
            {
                continue;
            }

            data.push_back(sale);
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading sales.\n";
    }

    return data;
}

vector<Sales> loadByYearSales(time_t currentDate)
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

            stringstream sss;
            tm *date = localtime(&currentDate);
            sss << put_time(date, "%Y-%m-%d");

            string currentYear = splitString(sss.str(), '-')[0];

            string saleDate = splitString(sale.currentTime, ' ')[0];
            string saleYear = splitString(saleDate, '-')[0];

            if (currentYear != saleYear)
            {
                continue;
            }

            data.push_back(sale);
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
    vector<Sales> sale = loadAllSales(), saleFiltered = loadSales(currentDate);

    string temp = "Are you sure you want to delete this sale history? [Y/N]";
    centerText(temp, temp.length());

    char ch = getch();

    while (true)
    {
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