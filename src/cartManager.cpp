#include "globalUtils.h"

using namespace std;

void saveCart(const vector<Cart> &data)
{
    ofstream outputFile("database/cart.txt");

    if (outputFile.is_open())
    {
        for (const Cart &cart : data)
        {
            outputFile << cart.productNumber << "," << cart.quantity << "\n";
        }

        outputFile.close();
    }
    else
    {
        cerr << "Error opening file for cart.\n";
    }
}

vector<Cart> loadCart()
{
    vector<Cart> data;

    ifstream inputFile("database/cart.txt");

    if (inputFile.is_open())
    {
        string line;

        while (getline(inputFile, line))
        {
            Cart cart;
            stringstream ss(line);
            string value;

            getline(ss, value, ',');
            cart.productNumber = stoi(value);

            getline(ss, value, ',');
            cart.quantity = stoi(value);

            data.push_back(cart);
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file for loading cart.\n";
    }

    return data;
}

void deleteProductInCart(int cartIndex)
{
    vector<Cart> cart = loadCart();

    string temp = "Are you sure you want to delete this item? [Y/N]";
    centerText(temp, temp.length());

    char ch = getch();

    while (true)
    {
        if (ch == 'y')
        {
            cart.erase(cart.begin() + cartIndex); // Delete item from cart
            saveCart(cart);

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
    vector<Cart> cart = loadCart();
    string temp;

    try
    {
        temp = "Enter new quantity: ";
        centerText(temp, temp.length());

        setInputPos(temp, temp.length(), maxHeight, -1, temp);
        cin >> temp;

        if (checkStock(cartIndex, stoi(temp))) // Check stock is enough
        {
            cart[cartIndex].quantity = stoi(temp);
            saveCart(cart);

            temp = "Item new quantity updated successfully!";
            centerText(temp, temp.length());
        }
        else if (stoi(temp) <= 0) // If less than 0 quantity, delete item
        {
            deleteProductInCart(cartIndex);
        }
        else // If stock is not enough
        {
            temp = "Stock is not enough to update quantity in cart.";
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