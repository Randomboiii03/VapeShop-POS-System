#include "globalUtils.h"

using namespace std;

void salesDisplay()
{
    vector<Product> products;

    for (string category : categories)
    {
        vector<Product> temp = loadProductsByCategory(category);
        products.insert(products.begin(), temp.begin(), temp.end()); // Insert all products of each category
    }

    vector<string> navigation, headerName, saleFilters, newBanner, newNavigation, content, options;
    string temp;

    vector<int> maxLengths;
    int prodListWidth = 0, bannerWidth, maxWidth, maxHeight, spaceBetween = 0, count = 0, optListWidth = 0, saleFilterListWidth = 0;
    float totalSales = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    navigation = navUser;

    headerName = {"No", "Date", "Product", "Quantity", "Price", "Total", "Payment Mode", "Transaction Number"};

    saleFilters = {"[0] All", "[1] Today", "[2] This Week", "[3] This Month", "[4] This Year"};

    options = {"[Esc] Close Menu", "[M] Menu", "[V] View Sale", "[D] Delete Sale", "[<->] Filter"};

    vector<Sales> sale = loadSales(); // Load sales

    for (int i = 0; i < headerName.size(); i++)
    {
        maxLengths.push_back(getMaxLengthSales(sale, products, i, headerName[i]));
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

    for (string filter : saleFilters)
    {
        saleFilterListWidth += filter.length(); // Sale filter list width
    }

    bannerWidth = banner[0].length() + 10; // Banner width

    do
    {
        spaceBetween += 3;
        maxWidth = prodListWidth + ((headerName.size() * spaceBetween) * 2) + (headerName.size() - 1); // Max width

        if (maxWidth > bannerWidth && maxWidth > prodListWidth)
        {
            break;
        }

    } while (true);

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Sales -" + splitString(saleFilters[saleFilterIndex], ']')[1]); // Banner display function

    maxHeight = max(navigation.size() + 10, newBanner.size() + sale.size() + 7); // Max height

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
        else if (i == 1 || i == (maxHeight - newBanner.size() - 3) || (i == (maxHeight - newBanner.size() - 5) && totalSales != 0)) // Divider display
        {
            temp = olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider();
        }
        else if (i == (maxHeight - newBanner.size() - 4) && totalSales != 0) // Total sales display
        {
            temp = "Total Sales: ₱ " + priceFormat(totalSales);

            padding = centerPadding(maxWidth, temp.length() - 2, 2);

            temp = olVLine() + addNRepeat(" ", padding.paddingLeft) + temp + addNRepeat(" ", padding.paddingRight) + olVLine();
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
            if (sale.size() > 0) // Sales list display
            {
                for (int j = 0; j < headerName.size(); j++)
                {
                    string detail = "";
                    int minus = 0;

                    for (int k = 0; k < products.size(); k++)
                    {
                        if (products[k].productID == sale[i - 2].productID)
                        {
                            switch (j)
                            {
                            case 0:
                                detail = to_string(i - 2); // Product number
                                break;
                            case 1:
                                detail = splitString(sale[i - 2].currentTime, ' ')[0]; // Date
                                break;
                            case 2:
                                detail = products[k].productName + " - " + products[k].category; // Product name and category
                                break;
                            case 3:
                                detail = to_string(sale[i - 2].quantity); // Product quantity
                                break;
                            case 4:
                                detail = "₱ " + priceFormat(products[k].price); // Price
                                minus = 2;                                      // For currency symbol
                                break;
                            case 5:
                                totalSales += products[k].price * sale[i - 2].quantity;

                                detail = "₱ " + priceFormat(products[k].price * sale[i - 2].quantity); // Total
                                minus = 2;                                                             // For currency symbol
                                break;
                            case 6:
                                detail = sale[i - 2].paymentMode; // Payment mode
                                break;
                            case 7:
                                if (sale[i - 2].transactionNum.length() > 5) // Transaction number if more than 5 digits
                                {
                                    detail = sale[i - 2].transactionNum.substr(0, 7) + "...";
                                }
                                else
                                {
                                    detail = sale[i - 2].transactionNum;
                                }
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
            else // When there is no sales
            {
                padding = centerPadding(maxHeight - newBanner.size() - 7, 1, 2);

                if (i == 2 + padding.paddingLeft + 1)
                {
                    temp = "No sales have been made yet.";
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
            salesDisplay();
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            salesDisplay();
        }
        else if (ch == 'v')
        {
        }
        else if (ch == 'd')
        {
        }
        else if (ch == 77) // Right
        {
            saleFilterIndex = (saleFilterIndex + 1) % saleFilters.size();
            salesDisplay();
        }
        else if (ch == 75) // Left
        {
            saleFilterIndex = (saleFilterIndex - 1 + saleFilters.size()) % saleFilters.size();
            salesDisplay();
        }
        else
        {
            globalMenu(ch);
        }
    }
}