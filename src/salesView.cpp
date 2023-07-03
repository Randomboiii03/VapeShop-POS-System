#include "globalUtils.h"

using namespace std;

void salesView(int salesID, time_t currentDate)
{
    vector<Sales> sale = loadSales(currentDate); // Load sales
    vector<Sales> saleFilter;
    vector<Product> products = loadAllProducts();

    vector<string> navigation, headerName, newBanner, newNavigation, content, options;
    string temp, date;

    vector<int> maxLengths;
    int prodListWidth = 0, bannerWidth, maxWidth, maxHeight, spaceBetween = 0, count = 0, optListWidth = 0;
    float totalSales = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    for (auto &sales : sale)
    {
        if (sales.salesID == salesID)
        {
            saleFilter.push_back(sales);
            date = splitString(sales.currentTime, ' ')[0];
        }
    }

    navigation = navAdmin;

    headerName = {"No", "Product Name", "Category", "Quantity", "Price", "Total"};
    maxLengths = {getMaxLengthSalesView(saleFilter, products, 0, headerName[0]),
                  getMaxLengthSalesView(saleFilter, products, 1, headerName[1]),
                  getMaxLengthSalesView(saleFilter, products, 2, headerName[2]),
                  getMaxLengthSalesView(saleFilter, products, 3, headerName[3]),
                  getMaxLengthSalesView(saleFilter, products, 4, headerName[4]),
                  getMaxLengthSalesView(saleFilter, products, 5, headerName[5])};
    
    options = {"[Esc] Close Menu", "[M] Menu", "[B] Back"};

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
        spaceBetween += 2;
        maxWidth = prodListWidth + ((headerName.size() * spaceBetween) * 2) + (headerName.size() - 1); // Max width

        if (maxWidth >= bannerWidth && maxWidth >= prodListWidth)
        {
            break;
        }

    } while (true);

    newBanner = bannerDisplay(maxWidth, bannerWidth, date); // Banner display function

    maxHeight = max(navigation.size() + 10, newBanner.size() + saleFilter.size() + 7); // Max height

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
        else if (i == 1 || i == ((maxHeight - newBanner.size()) - 3) || (i == (maxHeight - newBanner.size() - 5) && totalSales != 0)) // Divider display
        {
            temp = olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider();
        }
        else if (i == (maxHeight - newBanner.size() - 4) && totalSales != 0) // Total sales display
        {
            temp = "Total Sales: ₱ " + priceFormat(totalSales);

            padding = centerPadding(maxWidth, temp.length() - 2, 2);

            temp = olVLine() + addNRepeat(" ", padding.paddingLeft) + temp + addNRepeat(" ", padding.paddingRight) + olVLine();
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
            if (saleFilter.size() > i - 2) // Product list display
            {
                for (int j = 0; j < headerName.size(); j++)
                {
                    string detail = "";
                    int minus = 0;

                    for (auto &product : products)
                    {
                        if (product.productID == saleFilter[i - 2].productID)
                        {
                            switch (j)
                            {
                            case 0:
                                detail = to_string(i - 2); // Product number
                                break;
                            case 1:
                                detail = product.productName; // Brand
                                break;
                            case 2:
                                detail = product.category; // Product
                                break;
                            case 3:
                                detail = to_string(saleFilter[i - 2].quantity); // Stock
                                break;
                            case 4:
                                detail = "₱ " + priceFormat(saleFilter[i - 2].price); // Price
                                minus = 2;                                            // For currency symbol
                                break;
                            case 5:
                                totalSales += saleFilter[i - 2].price * saleFilter[i - 2].quantity;

                                detail = "₱ " + priceFormat(saleFilter[i - 2].price * saleFilter[i - 2].quantity); // Price
                                minus = 2;
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
            else // Empty space display
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
            salesView(salesID, currentDate);
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            salesView(salesID, currentDate);
        }
        else if (ch == 'b')
        {
            isOpen = false;
            salesDisplay(currentDate);
        }
        else
        {
            globalMenu(ch);
        }
    }
}