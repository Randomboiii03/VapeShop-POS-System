#include "globalUtils.h"

using namespace std;

void saveProducts(const vector<Product> &products)
{
    ofstream outputFile("database/products.txt");

    if (outputFile.is_open())
    {
        for (const Product &product : products)
        {
            outputFile << product.productNumber << "," << product.category << "," << product.brandName << "," << product.productName << "," << product.productDesc << "," << product.price << "," << product.stock << "," << product.isAvailable << "\n";
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

    ifstream inputFile("database/products.txt");

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

            if (category == product.category)
            {
                if (accountType != "Admin" && product.isAvailable == 0)
                {
                    continue;
                }

                products.push_back(product);
            }
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading products.\n";
    }

    return products;
}

void deleteProduct(int prodIndex)
{
    vector<Product> products, productsByCategory = loadProductsByCategory(categories[nextCateg]);

    for (string category : categories)
    {
        vector<Product> temp = loadProductsByCategory(category);
        products.insert(products.begin(), temp.begin(), temp.end());
    }

    string temp = "Are you sure you want to delete this product? [Y/N]";
    centerText(temp, temp.length());

    char ch = getch();

    while (true)
    {
        if (ch == 'y')
        {
            for (int i = 0; i < products.size(); i++)
            {
                if (products[i].productNumber == productsByCategory[prodIndex].productNumber)
                {
                    products.erase(products.begin() + i);
                    break;
                }
            }

            saveProducts(products);

            temp = "Product deleted successfully!";
            centerText(temp, temp.length());

            Sleep(2000);
            productDisplay();
        }
        else if (ch == 'n')
        {
            productDisplay();
        }
    }
}