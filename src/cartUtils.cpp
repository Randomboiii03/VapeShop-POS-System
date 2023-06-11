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
                string detail = product.productName + " - " + product.category;

                switch (columnIndex)
                {
                case 0:
                    max_length = max(max_length, static_cast<int>(to_string(data.size()).length()));
                    break;
                case 1:
                    max_length = max(max_length, static_cast<int>(detail.length()));
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

    max_length = max(max_length, static_cast<int>(headerName.length())); // Check for the header width

    return max_length;
}

bool checkStock(int cartIndex, int quantity)
{
    vector<Product> products;
    vector<Cart> cart = loadCart();

    int stock;

    for (string category : categories)
    {
        vector<Product> temp = loadProductsByCategory(category);
        products.insert(products.begin(), temp.begin(), temp.end());
    }

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].productNumber == cart[cartIndex].productNumber)
        {
            stock = products[i].stock;
            break;
        }
    }

    return stock >= quantity && quantity > 0; // Check stock is enough and quantity is greater than 0
}

void inCart(int prodIndex, int quantity)
{
    vector<Product> products = loadProductsByCategory(categories[nextCateg]);
    vector<Cart> cart = loadCart();

    string temp;
    bool isFound = false;

    for (int i = 0; i < cart.size(); i++)
    {
        if (cart[i].productNumber == products[prodIndex].productNumber) // Check product is in cart
        {
            if (checkStock(i, cart[i].quantity + quantity)) // Check stock is enough
            {
                cart[i].quantity += quantity;

                temp = "Product already in cart. Quantity updated successfully!";
                centerText(temp, temp.length());
            }
            else
            {
                temp = "Stock not enough for this product. Please enter a valid quantity.";
                centerText(temp, temp.length());
            }

            isFound = true;
            break;
        }
    }

    if (!isFound)
    {
        temp = "Product added to cart successfully!";
        centerText(temp, temp.length());

        Cart newCart = {products[prodIndex].productNumber, quantity};

        cart.push_back(newCart); // Add new item to cart
    }

    saveCart(cart); // Save cart to file
}