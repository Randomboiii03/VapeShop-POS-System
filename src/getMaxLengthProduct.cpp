#include "globalUtils.h"

using namespace std;

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