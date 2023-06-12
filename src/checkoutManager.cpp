#include "globalUtils.h"

using namespace std;

void addSales(const vector<Sales> &data)
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