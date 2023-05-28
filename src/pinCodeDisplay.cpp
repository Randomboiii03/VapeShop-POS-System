#include "globalUtils.h"

using namespace std;

void pinCodeDisplay()
{
    vector<string> navigation, compiledSideNav, compiledBanner, compiledContent;

    int totalLength = 0, adj, bannerSize, endSpacing, startSpacing;

    size_t sideNav, maxSizeCredential, maxSizeHeight, spacingMenu;

    ostringstream output;
    string temp, pin, options;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if (accountType == "Developer")
    {
        navigation = sideNavSuperAdmin;
    }
    else if (accountType == "Admin")
    {
        navigation = sideNavAdmin;
    }

    sideNav = navigation.size();

    totalLength = banner[1].length() + 10; // Total size of content w/o sideNav

    maxSizeHeight = max(sideNav, banner.size()) + 11; // Comparing height of sideNav and (banner + accounts)

    spacingMenu = ((maxSizeHeight - 2) - sideNav); // Get total spacing for sideNav

    spacingMenu = (spacingMenu / 2) + (spacingMenu % 2); // Get half of spacing for sideNav

    for (size_t i = 0; i < maxSizeHeight; i++) // Compile newSideNav
    {
        if (i == 0) // Compile top outline
        {
            compiledSideNav.push_back("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        }
        else if (i - spacingMenu - 1 < sideNav) // Compile sideNav
        {
            compiledSideNav.push_back(navigation[i - spacingMenu - 1]);
        }
        else if (i == maxSizeHeight - 1) // Compile bottom outline
        {
            compiledSideNav.push_back("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        }
        else // Compile spacing for sideNav < content
        {
            compiledSideNav.push_back("┃                                               ");
        }
    }

    bannerSize = banner[1].length();

    for (size_t i = 0; i <= banner.size(); i++) // Compile newBanner
    {
        temp = "";
        endSpacing = 0, startSpacing = 0;

        if (i <= banner.size())
        {
            if (i == banner.size()) // Get new bannerSize for title
            {
                temp = "PIN CODE";
                bannerSize = temp.length();
                temp = "";
            }

            endSpacing = (totalLength - bannerSize) / 2;
            startSpacing = endSpacing + ((totalLength - bannerSize) % 2);

            if (i == 0 && isOpen) // Add custom outline when menu isOpen
            {
                temp += "┳";
            }
            else if (i == 0 && !isOpen) // Add corner outline when menu !isOpen
            {
                temp += "┏";
            }
            else if (i == banner.size() - 1) // Add custom vertical divider
            {
                temp += "┣";
            }

            if (i == 0 || i == banner.size() - 1) // Add additional horizontal outline before and after of banner
            {
                for (size_t j = 0; j < startSpacing; j++)
                {
                    temp += "━";
                }

                temp += banner[i];

                for (size_t j = 0; j < endSpacing; j++)
                {
                    temp += "━";
                }

                if (i == 0)
                {
                    temp += "┓";
                }
                else
                {
                    temp += "┫";
                }
            }
            else // Add spacing before and after of banner < totalLength of accounts, and title
            {
                output << setw(startSpacing + 3) << left << "┃";

                if (i == banner.size())
                {
                    output << "PIN CODE";
                }
                else
                {
                    output << banner[i];
                }

                output << setw(endSpacing + 3) << right << "┃";
            }
        }

        if (temp == "")
        {
            temp = output.str();
            output = ostringstream();
        }

        compiledBanner.push_back(temp);
    }

    adj = compiledBanner.size();

    for (size_t i = adj; i < maxSizeHeight; i++) // Compile content
    {
        temp = "";
        
        if (i == adj || i == maxSizeHeight - 3) // Add divider between title and PIN code, and between PIN code and options
        {
            temp += "┣";

            for (size_t j = 0; j < totalLength; j++)
            {
                temp += "━";
            }

            temp += "┫";
        }
        else if (i == ((maxSizeHeight - adj - 4) / 2) + adj) // Add PIN Code details
        {
            pin = admin[0].pinCode;
            temp = "Admin PIN Code: " + pin;

            if (accountType != "Developer")
            {
                temp = "PIN Code: ";

                for (size_t j = 0; j < pin.length(); j++) // Encrypt PIN code
                {
                    if (j < pin.length() - 1)
                    {
                        temp += "*";
                    }
                    else
                    {
                        temp += pin[j];
                    }
                }
            }

            endSpacing = (totalLength - temp.length()) / 2;
            startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

            output << setw(startSpacing + 3) << left << "┃" << temp;
            output << setw(endSpacing + 3) << right << "┃";

            temp = "";
        }
        else if (i == maxSizeHeight - 2) // Add options
        {
            if (isOpen)
            {
                options = "[Esc] Close Menu";

                endSpacing = (totalLength - 35) / 3;
                startSpacing = endSpacing + ((totalLength - 35) % 3) + 1;
            }
            else
            {
                endSpacing = (totalLength - 27) / 3;
                startSpacing = endSpacing + ((totalLength - 27) % 3);

                options = "[M] Menu";
            }

            output << setw(startSpacing + 2) << left << "┃" << options;

            options = "[X] Change PIN Code";

            output << setw(startSpacing + 2) << left << "" << options;
            output << setw(endSpacing) << right << "┃";
        }
        else if (i == maxSizeHeight - 1) // Add horizontal outline for bottom of content
        {
            if (isOpen)
            {
                temp += "┻";
            }
            else
            {
                temp += "┗";
            }

            for (size_t j = 0; j < totalLength; j++)
            {
                temp += "━";
            }

            temp += "┛";
        }
        else // Add spacings
        {
            output << setw(totalLength + 3) << left << "┃"
                   << "┃";
        }

        if (temp == "")
        {
            temp = output.str();
            output = ostringstream();
        }

        compiledContent.push_back(temp);
    }

    // Display the whole UI
    for (size_t i = 0; i < maxSizeHeight; i++)
    {
        if (isOpen)
        {
            cout << compiledSideNav[i]; // Display sideNav
        }

        if (i < compiledBanner.size())
        {
            cout << compiledBanner[i]; // Display banner
        }
        else
        {
            cout << compiledContent[i - adj]; // Display content (header, data and options)
        }

        cout << endl;
    }

    while (true) // Menus
    {
        char ch = getch();

        if (ch == 'm' && !isOpen) // Open menu
        {
            isOpen = true;
            pinCodeDisplay();
        }
        else if (ch == 27 && isOpen) // Close menu
        {
            isOpen = false;
            pinCodeDisplay();
        }
        else if (ch == 'x') // Change PIN code
        {
            isOpen = false;
            pinCodeEditor();
        }
        else
        {
            globalMenu(ch);
        }
    }
}