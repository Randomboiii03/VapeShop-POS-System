#include "globalUtils.h"

using namespace std;

void checkoutDisplay(string paymentMode)
{
    vector<Product> products;
    vector<Cart> cart = loadCart();
    vector<Sales> sales;

    for (string category : categories)
    {
        vector<Product> temp = loadProductsByCategory(category);
        products.insert(products.begin(), temp.begin(), temp.end()); // Insert all products of each category
    }

    vector<string> navigation, headerName, newBanner, newNavigation, content, options;
    string temp, currentTime = getCurrentDateTime();

    vector<int> maxLengths;
    int prodListWidth = 0, bannerWidth, maxWidth, maxHeight, spaceBetween = 0, count = 0, optListWidth = 0;
    float totalPrice = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    navigation = navUser;

    headerName = {"Product", "Quantity", "Price", "Total"};

    options = {"[B] Back", "[C] Cash", "[E] E-Money", "[A] Credit Card"};

    for (int i = 1; i <= headerName.size(); i++)
    {
        maxLengths.push_back(getMaxLengthCart(cart, products, i, headerName[i - 1]));
    }

    for (int length : maxLengths)
    {
        prodListWidth += length; // Total product list width
    }

    for (int i = 0; i < options.size(); i++)
    {
        optListWidth += options[i].length();
    }

    bannerWidth = banner[0].length() + 10; // Banner width

    do
    {
        spaceBetween++;
        maxWidth = prodListWidth + ((headerName.size() * spaceBetween) * 2) + (headerName.size() - 1); // Max width

        if (maxWidth > bannerWidth)
        {
            break;
        }

    } while (true);

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Cart"); // Banner display function

    maxHeight = newBanner.size() + cart.size() + 7; // Max height

    for (int i = 0; i < maxHeight - newBanner.size(); i++) // Content display
    {
        temp = "";

        if (i == 0)
        {
            for (int j = 0; j < headerName.size(); j++) // Header display
            {
                padding = centerPadding(maxLengths[j], headerName[j].length(), 2);
                temp += olVLine() + addNRepeat(" ", padding.paddingLeft + spaceBetween) + headerName[j] + addNRepeat(" ", padding.paddingRight + spaceBetween);
            }

            temp += olVLine();
        }
        else if (i == 1 || i == (maxHeight - newBanner.size() - 3) || i == (maxHeight - newBanner.size() - 5)) // Divider display
        {
            temp = olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider();
        }
        else if (i == (maxHeight - newBanner.size() - 4)) // Total Price display
        {
            temp += olVLine();

            vector<string> tPrice = {currentTime, "", "Total Price:", "₱ " + priceFormat(totalPrice)};
            int minus = 0;

            for (int j = 0; j < headerName.size(); j++)
            {
                if (j == headerName.size() - 1)
                {
                    minus = 2;
                }
                else
                {
                    temp += " ";
                }

                padding = centerPadding(maxLengths[j], tPrice[j].length() - minus, 2);
                temp += addNRepeat(" ", padding.paddingLeft + spaceBetween) + tPrice[j] + addNRepeat(" ", padding.paddingRight + spaceBetween);
            }

            temp += olVLine();
        }
        else if (i == (maxHeight - newBanner.size() - 2)) // Options display
        {
            if (paymentMode == "")
            {
                padding = centerPadding(maxWidth, optListWidth, options.size() + 1);

                temp = olVLine() + addNRepeat(" ", padding.paddingLeft);

                for (int j = 0; j < options.size(); j++)
                {
                    temp += options[j] + addNRepeat(" ", padding.paddingRight);
                }

                temp += olVLine();
            }
            else
            {
                padding = centerPadding(maxWidth, paymentMode.length(), 2);
                temp = olVLine() + addNRepeat(" ", padding.paddingLeft) + paymentMode + addNRepeat(" ", padding.paddingRight) + olVLine();
            }
        }
        else if (i == (maxHeight - newBanner.size() - 1)) // Footer display
        {
            if (isOpen)
            {
                temp = olBHDivider();
            }
            else
            {
                temp = olBLCorner();
            }

            temp += addNRepeat(olHLine(), maxWidth) + olBRCorner();
        }
        else
        {
            if (cart.size() > 0) // Cart list display
            {
                for (int j = 0; j < headerName.size(); j++)
                {
                    string detail = "";
                    int minus = 0;

                    for (int k = 0; k < products.size(); k++)
                    {
                        if (products[k].productID == cart[i - 2].productID)
                        {
                            switch (j)
                            {
                            case 0:
                                detail = products[k].productName; // Product name
                                break;
                            case 1:
                                detail = to_string(cart[i - 2].quantity); // Product quantity
                                break;
                            case 2:
                                detail = "₱ " + priceFormat(products[k].price); // Price
                                minus = 2;                                      // For currency symbol
                                break;
                            case 3:
                                totalPrice += products[k].price * cart[i - 2].quantity;

                                detail = "₱ " + priceFormat(products[k].price * cart[i - 2].quantity); // Total
                                minus = 2;                                                             // For currency symbol
                                break;
                            default:
                                // Invalid column index
                                break;
                            }

                            break;
                        }
                    }

                    padding = centerPadding(maxLengths[j], detail.length() - minus, 2);
                    temp += olVLine() + addNRepeat(" ", padding.paddingLeft + spaceBetween) + detail + addNRepeat(" ", padding.paddingRight + spaceBetween);
                }

                temp += olVLine();
            }
            else // When there is no product
            {
                for (int length : maxLengths)
                {
                    temp += olVLine() + addNRepeat(" ", length + (spaceBetween * 2));
                }

                temp += olVLine();
            }
        }

        content.push_back(temp);
    }

    for (int i = 0; i < maxHeight; i++)
    {
        temp = "";

        if (i < newBanner.size())
        {
            temp += newBanner[i];
        }
        else
        {
            temp += content[i - newBanner.size()];
        }

        centerText(temp, maxWidth);
    }

    if (paymentMode == "")
    {
        while (true) // Menus
        {
            char ch = getch();

            if (ch == 'c')
            {
                checkoutDisplay("Cash");
            }
            else if (ch == 'e')
            {
                checkoutDisplay("E-Money");
            }
            else if (ch == 'a')
            {
                checkoutDisplay("Credit Card");
            }
            else if (ch == 'b')
            {
                cartDisplay();
            }
        }
    }
    else
    {
        string transactionNum;

        if (paymentMode == "Cash")
        {
            transactionNum = "N/A";
        }
        else if (paymentMode == "E-Money")
        {
            temp = "What type of e-money would you like to use? ";
            centerText(temp, temp.length());

            setInputPos(temp, temp.length(), 0, -1, temp);
            cin >> paymentMode;

            temp = "Enter transaction number: ";
            centerText(temp, temp.length());

            setInputPos(temp, temp.length(), 0, -1, temp);
            cin >> transactionNum;
        }
        else if (paymentMode == "Credit Card")
        {
            temp = "What type of credit card would you like to use? ";
            centerText(temp, temp.length());

            setInputPos(temp, temp.length(), 0, -1, temp);
            cin >> paymentMode;

            temp = "Enter transaction number: ";
            centerText(temp, temp.length());

            setInputPos(temp, temp.length(), 0, -1, temp);
            cin >> transactionNum;
        }

        temp = "Would you like to proceed to checkout? [Y/N]";
        centerText(temp, temp.length());

        while (true)
        {
            char ch = getch();

            if (ch == 'y')
            {
                for (auto &data : cart)
                {
                    for (auto &product : products)
                    {
                        if (data.productID == product.productID)
                        {
                            Sales sale = {data.productID, product.price, data.quantity, paymentMode, transactionNum, currentTime};
                            sales.push_back(sale);

                            break;
                        }
                    }
                }

                temp = "Checkout successful. Thank you!";
                centerText(temp, temp.length());

                saveSales(sales); // Save sales
                emptyCart(); // Empty cart

                Sleep(2000);
                cartDisplay();
            }
            else if (ch == 'n')
            {
                temp = "Cancel checkout";
                centerText(temp, temp.length());

                Sleep(2000);
                cartDisplay();
            }
        }
    }
}