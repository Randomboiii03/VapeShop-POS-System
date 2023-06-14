#include "globalUtils.h"

using namespace std;

bool containsCategory(const vector<string> &categories, const string &category)
{
    return find(categories.begin(), categories.end(), category) != categories.end();
}

vector<string> getCategories()
{
    vector<Product> products = loadAllProducts();
    vector<string> uniqueCategories;

    for(auto &product : products)
    {
        if(!containsCategory(uniqueCategories, product.category))
        {
            uniqueCategories.push_back(product.category);
        }
    }

    return uniqueCategories;
}

int getMaxLengthProduct(const vector<Product> &data, int columnIndex, string headerName)
{
    int maxLength = 0;

    // Check for the datas width
    for (const auto &product : data)
    {
        switch (columnIndex)
        {
        case 0:
            maxLength = max(maxLength, static_cast<int>(to_string(data.size()).length()));
            break;
        case 1:
            maxLength = max(maxLength, static_cast<int>(product.brandName.length()));
            break;
        case 2:
            maxLength = max(maxLength, static_cast<int>(product.productName.length()));
            break;
        case 3:
            maxLength = max(maxLength, static_cast<int>(product.category.length()));
            break;
        case 4:
            maxLength = max(maxLength, static_cast<int>(priceFormat(product.price).length() + 2));
            break;
        case 5:
            maxLength = max(maxLength, static_cast<int>(to_string(product.stock).length()));
            break;
        case 6:
            maxLength = max(maxLength, static_cast<int>((product.isAvailable ? string("Available") : string("Not Available")).length()));
            break;
        default:
            // Invalid column index
            break;
        }
    }

    // Check for the header width
    maxLength = max(maxLength, static_cast<int>(headerName.length()));

    return maxLength;
}