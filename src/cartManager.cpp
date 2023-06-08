#include "globalUtils.h"

using namespace std;

void deleteProductInCart(int cartIndex)
{
    string temp = "Are you sure you want to delete this item? [Y/N]";
    centerText(temp, temp.length());

    char ch = getch();

    while (true)
    {
        if (ch == 'y')
        {
            cart.erase(cart.begin() + cartIndex);

            temp = "Item deleted successfully!";
            centerText(temp, temp.length());

            Sleep(2000);
            cartDisplay();
        }
        else if (ch == 'n')
        {
            cartDisplay();
        }
    }
}

void editQuantityInCart(int cartIndex, int maxHeight)
{
    string temp;

    try
    {
        temp = "Enter new quantity: ";
        centerText(temp, temp.length());

        setInputPos(temp, temp.length(), maxHeight + 1, -1, temp);
        cin >> temp;

        if (checkStockinCart(cartIndex, stoi(temp)))
        {
            cart[cartIndex].quantity = stoi(temp);

            temp = "Item new quantity updated successfully!";
            centerText(temp, temp.length());
        }
        else if (stoi(temp) <= 0)
        {
            deleteProductInCart(cartIndex);
        }
        else
        {
            temp = "Invalid input. Please enter a valid quantity."; // Change this message
            centerText(temp, temp.length());
        }

        Sleep(2000);
        cartDisplay();
    }
    catch (const exception &) // Catch error
    {
        temp = "Invalid input. Please enter a valid quantity.";
        centerText(temp, temp.length());

        Sleep(2000);
        cartDisplay();
    }
}

bool checkStockinCart(int cartIndex, int quantity)
{
    vector<Product> products;

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

    return stock >= quantity && quantity > 0;
}

bool inCart(int prodIndex)
{
    vector<Product> products = loadProductsByCategory(categories[nextCateg]);

    for (int i = 0; i < cart.size(); i++)
    {
        if (cart[i].productNumber == products[prodIndex].productNumber)
        {
            return true;
        }
    }

    return false;
}