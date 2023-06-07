#include "globalUtils.h"

using namespace std;

void productView(int prodIndex)
{
    vector<Product> products = loadProductsByCategory(categories[nextCateg]);

    vector<string> navigation, newBanner, newNavigation, content, options;
    string temp, label;
    ostringstream oss;

    int bannerWidth, maxWidth, maxHeight, optListWidth = 0, spaceContent = 7, padDetails = 0, minus = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if (accountType == "User")
    {
        navigation = navUser;
        options = {"[Esc] Close Menu", "[M] Menu", "[B] Buy Now", "[A] Add to Cart"};
    }
    else if (accountType == "Admin")
    {
        navigation = navAdmin;
        options = {"[Esc] Close Menu", "[M] Menu", "[E] Edit Product", "[<->] Next Product"};

        spaceContent++;
    }

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    maxHeight = max(navigation.size() + 10, banner.size() + 14); // Max height

    newBanner = bannerDisplay(maxWidth, bannerWidth, categories[nextCateg]); // Banner display function

    padding = centerPadding(maxHeight - newBanner.size(), spaceContent, 2);

    for (int i = 0; i < padding.paddingLeft; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    spaceContent = padding.paddingRight; // Number of spaces between content and options

    label = "Name:";
    padding = centerPadding(maxWidth, label.length() + products[prodIndex].productName.length(), 2);
    padDetails = padding.paddingLeft;

    content.push_back(olVLine() + addNRepeat(" ", padDetails) + label + products[prodIndex].productName + addNRepeat(" ", padding.paddingRight) + olVLine());

    temp = "Brand:";
    padding = centerPadding(maxWidth, temp.length() + products[prodIndex].brandName.length(), 2);
    minus = temp.length() - label.length();

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + products[prodIndex].brandName + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Price: ";
    oss << fixed << setprecision(2) << products[prodIndex].price; // Add two decimal into the price

    padding = centerPadding(maxWidth, temp.length() + oss.str().length(), 2);
    minus = temp.length() - label.length() - 1;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + "₱ " + oss.str() + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus - 2) + olVLine());

    temp = "Stock/s: ";
    padding = centerPadding(maxWidth, temp.length() + to_string(products[prodIndex].stock).length(), 2);
    minus = temp.length() - label.length() - 1;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + to_string(products[prodIndex].stock) + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    if (accountType == "Admin")
    {
        temp = "Status: ";
        string status = products[prodIndex].isAvailable ? "Available" : "Not Available";

        padding = centerPadding(maxWidth, temp.length() + status.length(), 2);
        minus = temp.length() - label.length() - 1;
        cout << (padding.paddingLeft - padDetails);
        content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + status + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());
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
            productView(prodIndex);
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            productView(prodIndex);
        }
        else if (ch == 77) // Right
        {
            prodIndex = (prodIndex + 1) % products.size();
            productView(prodIndex);
        }
        else if (ch == 75) // Left
        {
            prodIndex = (prodIndex - 1 + products.size()) % products.size();
            productView(prodIndex);
        }
        else if (accountType == "User" && (ch == 'b' || ch == 'a'))
        {
            try
            {
                temp = "Enter quantity: ";

                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), maxHeight - 2, -1, temp);
                cin >> temp;

                stoi(temp); // Remove when function is created

                if (ch == 'b') // Buy now
                {
                    // checkout();
                }
                else if (ch == 'a') // Add to cart
                {
                    // cart();
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid PIN code.";
                centerText(temp, temp.length() + 10);

                Sleep(2000);
                productView(prodIndex);
            }
        }
        else if (accountType == "Admin" && ch == 'e') // Edit product
        {
            try
            {
                temp = "Choose product number: ";
                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), maxHeight - 2, -1, temp);
                cin >> temp;

                stoi(temp); // Remove when function is created

                // productEditor(stoi(temp));
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid PIN code.";
                centerText(temp, temp.length() + 10);

                Sleep(2000);
                productView(prodIndex);
            }
        }
        else
        {
            globalMenu(ch);
        }
    }
}