#include "globalUtils.h"

using namespace std;

void pinCodeDisplay()
{
    vector<string> navigation, newBanner, newNavigation, content, options;
    string temp;

    int bannerWidth, maxWidth, maxHeight, optListWidth = 0, spaceContent = 4;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if (accountType == "Admin")
    {
        navigation = navAdmin;
    }
    else if (accountType == "Developer")
    {
        navigation = navDeveloper;
        spaceContent++;
    }

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    maxHeight = max(navigation.size() + 10, banner.size() + 10); // Max height

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Pin Code Display"); // Banner display function

    padding = centerPadding(maxHeight - newBanner.size(), spaceContent, 2);

    for (int i = 0; i < padding.paddingLeft; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    spaceContent = padding.paddingRight; // Number of spaces between content and options

    temp = "Your Pin Code: ";

    if (accountType == "Admin") // If admin account type display pin code of admin
    {
        for (int i = 0; i < admin[0].pinCode.length(); i++)
        {
            if (i == admin[0].pinCode.length() - 1)
            {
                temp += admin[0].pinCode[i];
            }
            else
            {
                temp += "*";
            }
        }
    }
    else if (accountType == "Developer") // If developer account type display pin code of developer
    {
        temp += developer[0].pinCode;
    }

    padding = centerPadding(maxWidth, temp.length(), 2);

    content.push_back(olVLine() + addNRepeat(" ", padding.paddingLeft) + temp + addNRepeat(" ", padding.paddingRight) + olVLine());

    if (accountType == "Developer") // If developer account type display pin code of admin
    {
        temp = "Admin Pin Code: " + admin[0].pinCode;
        content.push_back(olVLine() + addNRepeat(" ", padding.paddingLeft) + temp + addNRepeat(" ", padding.paddingRight) + olVLine());
    }

    for (int i = 0; i < spaceContent; i++) // Space between enter pin code and options
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    content.push_back(olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider());

    options = {"[Esc] Close Menu", "[M] Menu", "[X] Change PIN Code"};

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
        if (!isOpen && i == 0)
        {
            continue;
        }
        else if (isOpen && i == 1)
        {
            continue;
        }

        temp += options[i] + addNRepeat(" ", padding.paddingRight);
    }

    temp += olVLine();

    content.push_back(temp); // Options display

    content.push_back(olBLCorner() + addNRepeat(olHLine(), maxWidth) + olBRCorner()); // Footer display

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
            pinCodeDisplay();
        }
        else if (ch == 27) // Close menu
        {
            isOpen = false;
            pinCodeDisplay();
        }
        else if (ch == 'x') // Change pin code
        {
            pinCodeEditor();
        }
        else
        {
            globalMenu(ch);
        }
    }
}