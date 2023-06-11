#include "globalUtils.h"

using namespace std;

bool containsCategory(const vector<string> &categories, const string &category)
{
    return find(categories.begin(), categories.end(), category) != categories.end();
}

vector<string> getCategories()
{
    vector<string> uniqueCategories;

    fstream inputFile("database/products.txt");

    if (inputFile.is_open())
    {
        string line;

        while (getline(inputFile, line))
        {
            Product product;
            stringstream ss(line);
            string value;

            getline(ss, value, ',');
            product.productID = stoi(value);

            getline(ss, product.category, ',');

            getline(ss, product.brandName, ',');

            getline(ss, product.productName, ',');

            getline(ss, product.productDesc, ',');

            getline(ss, value, ',');
            product.price = stoi(value);

            getline(ss, value, ',');
            product.stock = stoi(value);

            getline(ss, value);
            product.isAvailable = stoi(value);

            if (!containsCategory(uniqueCategories, product.category))
            {
                uniqueCategories.push_back(product.category);
            }
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for getting categories.\n";
    }

    return uniqueCategories;
}

int getMaxLengthProduct(const vector<Product> &data, int columnIndex, string headerName)
{
    int max_length = 0;

    // Check for the datas width
    for (const auto &product : data)
    {
        switch (columnIndex)
        {
        case 0:
            max_length = max(max_length, static_cast<int>(to_string(data.size()).length()));
            break;
        case 1:
            max_length = max(max_length, static_cast<int>(product.brandName.length()));
            break;
        case 2:
            max_length = max(max_length, static_cast<int>(product.productName.length()));
            break;
        case 3:
            max_length = max(max_length, static_cast<int>(product.category.length()));
            break;
        case 4:
            max_length = max(max_length, static_cast<int>(priceFormat(product.price).length() - 2));
            break;
        case 5:
            max_length = max(max_length, static_cast<int>(to_string(product.stock).length()));
            break;
        case 6:
            max_length = max(max_length, static_cast<int>((product.isAvailable ? string("Available") : string("Not Available")).length()));
            break;
        default:
            // Invalid column index
            break;
        }
    }

    // Check for the header width
    max_length = max(max_length, static_cast<int>(headerName.length()));

    return max_length;
}