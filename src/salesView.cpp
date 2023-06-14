#include "globalUtils.h"

using namespace std;

void salesView(int saleIndex, time_t currentDate)
{
    vector<Product> products;
    vector<Sales> sale = loadSales(currentDate); // Load sales

    for (string category : categories)
    {
        vector<Product> temp = loadProductsByCategory(category);
        products.insert(products.begin(), temp.begin(), temp.end()); // Insert all products of each category
    }

    vector<string> navigation, newBanner, newNavigation, content, options;
    string temp, label;

    int bannerWidth, maxWidth, maxHeight, optListWidth = 0, spaceContent = 10, padDetails = 0, minus = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    navigation = navAdmin;
    options = {"[Esc] Close Menu", "[M] Menu", "[B] Back"};

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    newBanner = bannerDisplay(maxWidth, bannerWidth, getSalesTitle(currentDate)); // Banner display function

    maxHeight = max(navigation.size() + 10, newBanner.size() + 16); // Max height

    padding = centerPadding(maxHeight - newBanner.size(), spaceContent, 2);

    for (int i = 0; i < padding.paddingLeft; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    spaceContent = padding.paddingRight; // Number of spaces between content and options

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].productID == sale[saleIndex].productID)
        {
            label = "Product Name: ";
            temp = label + products[i].productName + " - " + products[i].category;
            padding = centerPadding(maxWidth, temp.length(), 2);
            padDetails = padding.paddingLeft;

            content.push_back(olVLine() + addNRepeat(" ", padDetails) + temp + addNRepeat(" ", padding.paddingRight) + olVLine());
            break;
        }
    }

    temp = "Date of Sale: " + sale[saleIndex].currentTime;
    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Sale Price: ₱ " + priceFormat(sale[saleIndex].price);
    padding = centerPadding(maxWidth, temp.length() - 2, 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Quantity: " + to_string(sale[saleIndex].quantity);
    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Total: ₱ " + priceFormat(sale[saleIndex].price * sale[saleIndex].quantity);
    padding = centerPadding(maxWidth, temp.length() - 2, 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Payment Mode: " + sale[saleIndex].paymentMode;
    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Transaction Number: " + sale[saleIndex].transactionNum;
    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    for (int i = 0; i < spaceContent; i++) // Space between enter pin code and options
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    content.push_back(olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider());

    for (int i = 0; i < options.size(); i++) // Option list width
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

    padding = centerPadding(maxWidth, optListWidth, options.size());
    temp = olVLine() + addNRepeat(" ", padding.paddingLeft);

    for (int i = 0; i < options.size(); i++)
    {
        if (!isOpen && i == 0) // If menu is closed skip [Esc] Close Menu
        {
            continue;
        }
        else if (isOpen && i == 1) // If menu is open [M] Menu
        {
            continue;
        }

        temp += options[i] + addNRepeat(" ", padding.paddingRight);
    }

    temp += olVLine();

    content.push_back(temp); // Options display

    if (isOpen)
    {
        temp = olBHDivider();
    }
    else
    {
        temp = olBLCorner();
    }

    content.push_back(temp + addNRepeat(olHLine(), maxWidth) + olBRCorner()); // Footer display

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
            salesView(saleIndex, currentDate);
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            salesView(saleIndex, currentDate);
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