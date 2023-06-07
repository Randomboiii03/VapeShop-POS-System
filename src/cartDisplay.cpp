#include "globalUtils.h"

using namespace std;

void cartDisplay()
{
    vector<Product> products;

    for (string category : categories)
    {
        vector<Product> temp = loadProductsByCategory(category);
        products.insert(products.begin(), temp.begin(), temp.end());
    }

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

    options = {"[Esc] Close Menu", "[M] Menu", "[E] Edit Product", "[D] Delete Product", "[T] Checkout"};

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

        if (maxWidth > bannerWidth)
        {
            break;
        }

    } while (true);

    maxHeight = max(navigation.size() + 10, banner.size() + cart.size() + 9); // Max height

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Cart"); // Banner display function

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
        else if (i == 1 || i == (maxHeight - newBanner.size() - 4)) // Total Price display
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
        else if (i == 1 || i == (maxHeight - newBanner.size() - 2)) // Options display
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
                        if (products[k].productNumber == cart[i - 2].productNumber)
                        {
                            switch (j)
                            {
                            case 0:
                                detail = to_string(i - 2); // Product number
                                break;
                            case 1:
                                detail = products[k].productName; // Product name
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
            // checkout();
        }
        else if (ch == 'd' || ch == 'e')
        {
            try
            {
                temp = "Enter product number: ";

                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), maxHeight - 2, -1, temp);
                cin >> temp;

                stoi(temp); // Remove when function is created

                if (ch == 'd') // Delete product in cart
                {
                    // cartDelete(stoi(temp));
                }
                else if (ch == 'e') // Edit product in cart
                {
                    // cartEdit(stoi(temp));
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid PIN code.";
                centerText(temp, temp.length() + 10);

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