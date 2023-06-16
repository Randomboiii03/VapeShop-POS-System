#include "globalUtils.h"

using namespace std;

void productView(int prodIndex, vector<Product> products)
{
    vector<string> navigation, newBanner, newNavigation, content, options;
    string temp, label;

    int bannerWidth, maxWidth, maxHeight, optListWidth = 0, spaceContent = 7, padDetails = 0, minus = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if (accountType == "User")
    {
        navigation = navUser;
        options = {"[Esc] Close Menu", "[M] Menu", "[A] Add to Cart", "[◀️▶️] Next Product", "[B] Back"};
    }
    else if (accountType == "Admin")
    {
        navigation = navAdmin;
        options = {"[Esc] Close Menu", "[M] Menu", "[E] Edit Product", "[◀️▶️] Next Product", "[B] Back"};

        spaceContent++;
    }

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    newBanner = bannerDisplay(maxWidth, bannerWidth, products[prodIndex].category); // Banner display function

    maxHeight = max(navigation.size() + 10, newBanner.size() + 13); // Max height

    padding = centerPadding(maxHeight - newBanner.size(), spaceContent, 2);

    for (int i = 0; i < padding.paddingLeft; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    spaceContent = padding.paddingRight; // Number of spaces between content and options

    label = "Name: ";
    temp = label + products[prodIndex].productName;

    padding = centerPadding(maxWidth, temp.length(), 2);
    padDetails = padding.paddingLeft;

    content.push_back(olVLine() + addNRepeat(" ", padDetails) + temp + addNRepeat(" ", padding.paddingRight) + olVLine());

    temp = "Brand: " + products[prodIndex].brandName;

    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Price: ₱ " + priceFormat(products[prodIndex].price);

    padding = centerPadding(maxWidth, temp.length() - 2, 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Stock/s: " + to_string(products[prodIndex].stock);

    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    if (accountType == "Admin")
    {
        string status = products[prodIndex].isAvailable ? "Available" : "Not Available";
        temp = "Status: " + status;

        padding = centerPadding(maxWidth, temp.length(), 2);
        minus = splitString(temp, ':')[0].length() - label.length() + 2;
        
        content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp +  addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());
    }

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

    optListWidth -= 8;

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
            productView(prodIndex, products);
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            productView(prodIndex, products);
        }
        else if (ch == 77) // Right
        {
            prodIndex = (prodIndex + 1) % products.size();
            productView(prodIndex, products);
        }
        else if (ch == 75) // Left
        {
            prodIndex = (prodIndex - 1 + products.size()) % products.size();
            productView(prodIndex, products);
        }
        else if (ch == 'b') // Left
        {
            isOpen = false;
            productDisplay();
        }
        else if (accountType == "User" && ch == 'a')
        {
            try
            {
                temp = "Enter quantity: ";

                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), 0, -1, temp);
                cin >> temp;

                if (stoi(temp) > 0)
                {
                    inCart(prodIndex, stoi(temp));

                    Sleep(2000);
                    productDisplay();
                }
                else
                {
                    temp = "Invalid input. Please enter a valid quantity.";
                    centerText(temp, temp.length());

                    Sleep(2000);
                    productView(prodIndex, products);
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid quantity.";
                centerText(temp, temp.length());

                Sleep(2000);
                productView(prodIndex, products);
            }
        }
        else if (accountType == "Admin" && ch == 'e') // Edit product
        {
            productEditor(products[prodIndex].productID, 0);
        }
        else
        {
            globalMenu(ch);
        }
    }
}