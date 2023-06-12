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
        cerr << "Error opening file for cart.\n";
    }
}

vector<Sales> loadSales()
{
    vector<Sales> data;

    switch (saleFilterIndex)
    {
    case 0:
        data = loadAllSales();
        break;
    case 1:
        data = loadTodaySales();
        break;
    case 2:
        data = loadThisWeekSales();
        break;
    case 3:
        data = loadThisMonthSales();
        break;
    case 4:
        data = loadThisYearSales();
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

vector<Sales> loadTodaySales()
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

            string currentDate = splitString(getCurrentDateTime(), ' ')[0];
            string saleDate = splitString(sale.currentTime, ' ')[0];

            if (currentDate != saleDate)
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

vector<Sales> loadThisWeekSales()
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

            for (string date : getWeekDates())
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

vector<Sales> loadThisMonthSales()
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

            string currentDate = splitString(getCurrentDateTime(), ' ')[0];
            string currentMonth = splitString(currentDate, '-')[0] + "-" + splitString(currentDate, '-')[1];

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

vector<Sales> loadThisYearSales()
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

            string currentDate = splitString(getCurrentDateTime(), ' ')[0];
            string currentYear = splitString(currentDate, '-')[0];

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