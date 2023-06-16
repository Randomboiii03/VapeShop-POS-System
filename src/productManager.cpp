#include "globalUtils.h"

using namespace std;

void saveProducts(const vector<Product> &products)
{
    ofstream outputFile("database/products.txt");

    if (outputFile.is_open())
    {
        for (const Product &product : products)
        {
            outputFile << product.productID << "," << product.category << "," << product.brandName << "," << product.productName << "," << product.productDesc << "," << product.price << "," << product.stock << "," << product.isAvailable << "\n";
        }

        outputFile.close();
    }
    else
    {
        cerr << "Error opening file for products.\n";
    }
}

vector<Product> loadAllProducts()
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

vector<Product> loadProductsByCategory(const string &category)
{
    vector<Product> products = loadAllProducts(), result;

    for (auto &product : products)
    {
        if (product.category == category)
        {
            if ((accountType != "Admin" && !product.isAvailable) || product.stock <= 0)
            {
                continue;
            }

            result.push_back(product);
        }
    }

    return result;
}

void deleteProduct(int prodIndex, vector<Product> products)
{
    vector<Product> allProducts = loadAllProducts();

    string temp = "Are you sure you want to delete this product? [Y/N]";
    centerText(temp, temp.length());

    while (true)
    {
        char ch = getch();

        if (ch == 'y')
        {
            for (int i = 0; i < allProducts.size(); i++)
            {
                if (allProducts[i].productID == products[prodIndex].productID)
                {
                    allProducts.erase(allProducts.begin() + i);
                    break;
                }
            }

            saveProducts(allProducts);
            categories = getCategories();

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

vector<Product> searchProductsByName(const string &substring)
{
    vector<Product> results;

    string searchTerm = toLowercase(substring);

    for (string category : categories)
    {
        vector<Product> products = loadProductsByCategory(category);

        for (Product product : products)
        {
            string name = toLowercase(product.productName);

            if (name.find(searchTerm) != string::npos)
            {
                results.push_back(product);
            }
        }
    }

    return results;
}
