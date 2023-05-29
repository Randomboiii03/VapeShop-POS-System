#include "globalUtils.h"

using namespace std;

void saveProductsByCategory(const vector<Product> &products, const string &category)
{
    ofstream outputFile("databaseFolder/products/" + category + ".txt");

    if (outputFile.is_open())
    {
        for (const Product &product : products)
        {
            if (product.category == category)
            {
                outputFile << product.productNumber << ", " << product.category << ", " << product.brandName << ", " << product.productName << ", " << product.productDesc << ", " << product.price << ", " << product.stock << ", " << product.isAvailable << "\n";
            }
        }
        outputFile.close();
    }
    else
    {
        cerr << "Error opening file for products.\n";
    }
}

vector<Product> loadProductsByCategory(const string &category)
{
    vector<Product> products;

    ifstream inputFile("databaseFolder/products/" + category + ".txt");

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            Product product;
            stringstream ss(line);
            string value;
            getline(ss, value, ',');
            product.productNumber = stoi(value);
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
            products.push_back(product);
        }
        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading products.\n";
    }
    return products;
}

vector<string> getCategories(const string &folderPath)
{
    vector<string> fileNames;

    // Iterate over files in the folder
    for (const auto &entry : filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            string fileName = entry.path().filename().string();

            // Check if the file has a .txt extension
            if (fileName.size() > 4 && fileName.substr(fileName.size() - 4) == ".txt")
            {
                // Remove the .txt extension
                fileName = fileName.substr(0, fileName.size() - 4);
                fileNames.push_back(fileName);
            }
        }
    }

    return fileNames;
}