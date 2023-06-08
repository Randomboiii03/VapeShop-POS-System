#include "globalUtils.h"

using namespace std;

void productDisplay()
{
    vector<Product> products = loadProductsByCategory(categories[nextCateg]);

    vector<string> navigation, headerName, newBanner, newNavigation, content, options;
    string temp;

    vector<int> maxLengths;
    int prodListWidth = 0, bannerWidth, maxWidth, maxHeight, spaceBetween = 0, count = 0, optListWidth = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if (accountType == "User")
    {
        navigation = navUser;

        headerName = {"No", "Brand", "Product Name", "Price"};
        maxLengths = {getMaxLengthProduct(products, 0, headerName[0]),
                      getMaxLengthProduct(products, 1, headerName[1]),
                      getMaxLengthProduct(products, 2, headerName[2]),
                      getMaxLengthProduct(products, 4, headerName[3])};

        options = {"[Esc] Close Menu", "[M] Menu", "[V] View Product", "[<->] Next Category"};
    }
    else if (accountType == "Admin")
    {
        navigation = navAdmin;

        headerName = {"No", "Brand", "Product Name", "Price", "Stock", "Status"};
        maxLengths = {getMaxLengthProduct(products, 0, headerName[0]),
                      getMaxLengthProduct(products, 1, headerName[1]),
                      getMaxLengthProduct(products, 2, headerName[2]),
                      getMaxLengthProduct(products, 4, headerName[3]),
                      getMaxLengthProduct(products, 5, headerName[4]),
                      getMaxLengthProduct(products, 6, headerName[5])};

        options = {"[Esc] Close Menu", "[M] Menu", "[V] View & Edit Product", "[D] Delete Product", "[A] Add Product", "[<->] Next Category"};
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

    newBanner = bannerDisplay(maxWidth, bannerWidth, categories[nextCateg]); // Banner display function

    maxHeight = max(navigation.size() + 10, newBanner.size() + products.size() + 5); // Max height

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
        else if (i == 1 || i == ((maxHeight - newBanner.size()) - 3)) // Divider display
        {
            temp = olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider();
        }
        else if (i == ((maxHeight - newBanner.size()) - 2)) // Options display
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
        else if (i == ((maxHeight - newBanner.size()) - 1)) // Footer display
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
            if (products.size() > 0) // Product list display
            {
                for (int j = 0; j < headerName.size(); j++)
                {
                    string detail = "";
                    int minus = 0;

                    switch (j)
                    {
                    case 0:
                        detail = to_string(i - 2); // Product number
                        break;
                    case 1:
                        detail = products[i - 2].brandName; // Brand
                        break;
                    case 2:
                        detail = products[i - 2].productName; // Product
                        break;
                    case 3:
                        detail = "₱ " + priceFormat(products[i - 2].price); // Price
                        minus = 2;                                          // For currency symbol
                        break;
                    case 4:
                        detail = to_string(products[i - 2].stock); // Stock
                        break;
                    case 5:
                        detail = products[i - 2].isAvailable ? "Available" : "Not Available"; // Status
                        break;
                    default:
                        // Invalid column index
                        break;
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
            productDisplay();
        }
        else if (ch == 27) // Close menu
        {
            if (isOpen)
            {
                isOpen = false;
                productDisplay();
            }
            else
            {
                count++;

                if (count >= 10)
                {
                    ExpectedTimeData timeData = loadExpectedTime();

                    if (tries >= 5 && !checkTime(timeData.expectedTime))
                    {
                        temp = "Maximum login attempts reached. Please wait for one hour before trying again.";
                        centerText(temp, temp.length());
                    }
                    else if (checkTime(timeData.expectedTime))
                    {
                        pinCodeLogin();
                    }
                }
            }
        }
        else if (ch == 77) // Right
        {
            nextCateg = (nextCateg + 1) % categories.size();
            productDisplay();
        }
        else if (ch == 75) // Left
        {
            nextCateg = (nextCateg - 1 + categories.size()) % categories.size();
            productDisplay();
        }
        else if (ch == 'v') // View product
        {
            try
            {
                temp = "Choose product number: ";

                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), 0, -1, temp);
                // cout << to_string(maxHeight) << endl;
                cin >> temp;

                if (stoi(temp) < products.size() && stoi(temp) >= 0)
                {
                    productView(stoi(temp));
                }
                else
                {
                    temp = "Invalid input. Please enter a valid product number.";
                    centerText(temp, temp.length());

                    Sleep(2000);
                    productDisplay();
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid product number.";
                centerText(temp, temp.length());

                Sleep(2000);
                productDisplay();
            }
        }
        else if (accountType == "Admin" && (ch == 'a' || ch == 'd'))
        {
            try
            {
                temp = "Choose product number: ";
                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), 0, -1, temp);
                cin >> temp;

                if (stoi(temp) < products.size() && stoi(temp) >= 0)
                {
                    if (ch == 'a') // Add product
                    {
                        // productAdd();
                    }
                    else if (ch == 'd') // Delete product
                    {
                        deleteProduct(stoi(temp));
                    }
                }
                else
                {
                    temp = "Invalid input. Please enter a valid product number.";
                    centerText(temp, temp.length());

                    Sleep(2000);
                    productDisplay();
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid product number.";
                centerText(temp, temp.length());

                Sleep(2000);
                productDisplay();
            }
        }
        else
        {
            globalMenu(ch);
        }
    }
}