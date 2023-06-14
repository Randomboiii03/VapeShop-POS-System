#include "globalUtils.h"

using namespace std;

void cartDisplay()
{
    vector<Product> products = loadAllProducts();
    vector<Cart> cart = loadCart();

    vector<string> navigation, headerName, newBanner, newNavigation, content, options;
    string temp;

    vector<int> maxLengths;
    int prodListWidth = 0, bannerWidth, maxWidth, maxHeight, spaceBetween = 0, count = 0, optListWidth = 0;
    float totalPrice = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    navigation = navUser;

    headerName = {"No", "Product", "Quantity", "Price", "Total"};

    options = {"[Esc] Close Menu", "[M] Menu", "[E] Edit Quantity", "[D] Delete Product", "[T] Checkout"};

    for (int i = 0; i < headerName.size(); i++)
    {
        maxLengths.push_back(getMaxLengthCart(cart, products, i, headerName[i]));
    }

    for (int length : maxLengths)
    {
        prodListWidth += length; // Total product list width
    }

    for (int i = 0; i < options.size(); i++)
    {
        if (!isOpen && i == 0)
        {
            continue;
        }
        else if (isOpen && i == 1)
        {
            continue;
        }

        optListWidth += options[i].length();
    }

    bannerWidth = banner[0].length() + 10; // Banner width

    do
    {
        spaceBetween++;
        maxWidth = prodListWidth + ((headerName.size() * spaceBetween) * 2) + (headerName.size() - 1); // Max width

        if (maxWidth > bannerWidth && maxWidth > prodListWidth)
        {
            break;
        }

    } while (true);

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Cart"); // Banner display function

    maxHeight = max(navigation.size() + 10, newBanner.size() + cart.size() + 7); // Max height

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
        else if (i == 1 || i == (maxHeight - newBanner.size() - 3) || (i == (maxHeight - newBanner.size() - 5) && totalPrice != 0)) // Divider display
        {
            temp = olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider();
        }
        else if (i == (maxHeight - newBanner.size() - 4) && totalPrice != 0) // Total price display
        {
            temp += olVLine();

            vector<string> tPrice = {"", "", "", "Total Price:", "₱ " + priceFormat(totalPrice)};
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
            padding = centerPadding(maxWidth, optListWidth, options.size());

            temp = olVLine() + addNRepeat(" ", padding.paddingLeft);

            for (int j = 0; j < options.size(); j++)
            {
                if (!isOpen && j == 0) // If menu is closed skip [Esc] Close Menu
                {
                    continue;
                }
                else if (isOpen && j == 1) // If menu is open skip [M] Menu
                {
                    continue;
                }

                temp += options[j] + addNRepeat(" ", padding.paddingRight);
            }

            temp += olVLine();
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
                                detail = to_string(i - 2); // Product number
                                break;
                            case 1:
                                detail = products[k].productName + " - " + products[k].category; // Product name and category
                                break;
                            case 2:
                                detail = to_string(cart[i - 2].quantity); // Product quantity
                                break;
                            case 3:
                                detail = "₱ " + priceFormat(products[k].price); // Price
                                minus = 2;                                      // For currency symbol
                                break;
                            case 4:
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
                padding = centerPadding(maxHeight - newBanner.size() - 7, 1, 2);

                if (i == 2 + padding.paddingLeft + 1)
                {
                    temp = "No item in cart";
                    padding = centerPadding(maxWidth, temp.length(), 2);

                    temp = olVLine() + addNRepeat(" ", padding.paddingLeft) + temp + addNRepeat(" ", padding.paddingRight) + olVLine();
                }
                else
                {
                    temp = olVLine() + addNRepeat(" ", maxWidth) + olVLine();
                }
            }
        }

        content.push_back(temp);
    }

    if (isOpen)
    {
        maxWidth += navigation[2].length() + 1;                   // Navigation width
        newNavigation = navigationDisplay(navigation, maxHeight); // Navigation display function
    }

    for (int i = 0; i < maxHeight; i++)
    {
        temp = "";

        if (isOpen)
        {
            temp = newNavigation[i];
        }

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

    while (true) // Menus
    {
        char ch = getch();

        if (ch == 'm' && !isOpen) // Open menu
        {
            isOpen = true;
            cartDisplay();
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            cartDisplay();
        }
        else if (ch == 't') // Checkout
        {
            isOpen = false;

            if (cart.size() > 0)
            {
                checkoutDisplay("");
            }
            else
            {
                temp = "There is no product in cart.";
                centerText(temp, temp.length());

                Sleep(2000);
                cartDisplay();
            }
        }
        else if (ch == 'd' || ch == 'e')
        {
            try
            {
                temp = "Enter product number: ";
                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), 0, -1, temp);
                cin >> temp;

                if (stoi(temp) < cart.size() && stoi(temp) >= 0)
                {
                    if (ch == 'd') // Delete product in cart
                    {
                        deleteProductInCart(stoi(temp));
                    }
                    else if (ch == 'e') // Edit product in cart
                    {
                        editQuantityInCart(stoi(temp), maxHeight);
                    }
                }
                else
                {
                    temp = "Invalid input. Please enter a valid product number.";
                    centerText(temp, temp.length());

                    Sleep(2000);
                    cartDisplay();
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid product number.";
                centerText(temp, temp.length());

                Sleep(2000);
                cartDisplay();
            }
        }
        else
        {
            globalMenu(ch);
        }
    }
}