#include "globalUtils.h"

using namespace std;

int getMaxLengthCart(const vector<Cart> &data, const vector<Product> &data2, int columnIndex, string headerName)
{
    int max_length = 0;

    // Check for the datas width
    for (const auto &cart : data)
    {
        for (const auto &product : data2)
        {
            if (cart.productNumber == product.productNumber)
            {
                switch (columnIndex)
                {
                case 0:
                    max_length = max(max_length, static_cast<int>(to_string(data.size()).length()));
                    break;
                case 1:
                    max_length = max(max_length, static_cast<int>(product.productName.length()));
                    break;
                case 2:
                    max_length = max(max_length, static_cast<int>(to_string(cart.quantity).length()));
                    break;
                case 3:
                    max_length = max(max_length, static_cast<int>(priceFormat(product.price).length() - 2));
                    break;
                case 4:
                    max_length = max(max_length, static_cast<int>(priceFormat(product.price * cart.quantity).length() - 2));
                    break;
                default:
                    // Invalid column index
                    break;
                }

                break;
            }
        }
    }

    // Check for the header width
    max_length = max(max_length, static_cast<int>(headerName.length()));

    return max_length;
}