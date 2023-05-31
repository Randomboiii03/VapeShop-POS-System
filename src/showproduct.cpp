#include "globalUtils.h"

using namespace std;

void showproduct(string category, int productIndex)
{
     vector<Product> products = loadProductsByCategory(category);

    vector<string> navigation, compiledSideNav, compiledBanner, compiledContent, columnName;
    vector<int> maxLengths;

    int totalLength = 0, adj, additionalDividerWidth = 6, num, bannerSize;
    size_t sideNav, maxSizeHeight, spacingMenu;

    ostringstream output;
    string temp, pin, options;

    Padding padding;

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

    totalLength = banner[1].length() + 10; // Total size of content w/o side navigation

    maxSizeHeight = max(sideNav, banner.size()) + 11; // Compare height of side navigation and (banner + accounts)

    padding = centerPadding(static_cast<int>(maxSizeHeight) - 2, static_cast<int>(sideNav), 2); // Get left and right padding

    bannerSize = banner[1].length();

    compiledSideNav = navigationDisplay(navigation, maxSizeHeight, sideNav, padding.paddingLeft); // Compile side navigation

    for (size_t i = 0; i <= banner.size(); i++) // Compile banner
    {
        temp = bannerDisplay(i, bannerSize, totalLength, "PIN CODE"); // Compile banner
        compiledBanner.push_back(temp);
    }

    adj = compiledBanner.size();

 for (size_t i = adj; i < maxSizeHeight; i++) // Compile content
    {
        temp = "";

        if (i == adj || i == maxSizeHeight - 3) // Add divider between title and PIN code, and between PIN code and options
        {
            temp += "┣" + addSpacingWithOutline(totalLength) + "┫";
        }
        else if (i == ((maxSizeHeight - adj - 4) / 2) + adj) // Add PIN Code details
        {
           //llll
           padding = centerPadding(totalLength, products[productIndex].productName.length(),2);
           output <<"┃"<<setw(padding.paddingLeft)<< left << "" <<products[productIndex].productName;
           output <<setw(padding.paddingRight)<< right <<""<<"┃"<<endl;
           padding = centerPadding(totalLength, products[productIndex].brandName.length(),2);
           output <<"┃"<<setw(padding.paddingLeft)<< left << "" <<products[productIndex].brandName;
           output <<setw(padding.paddingRight)<< right <<""<<"┃"<<endl;
            ostringstream oss;
                oss << fixed << setprecision(2) << products[i - 13].price;
                padding = centerPadding(totalLength,oss.str().length()+2,2);
           output <<"┃"<<setw(padding.paddingLeft)<< left << "" <<"₱ " << oss.str();
           output <<setw(padding.paddingRight)<< right <<""<<"┃";

        }
        else if (i == maxSizeHeight - 2) // Add options
        {
            if (isOpen)
            {
                options = "[Esc] Close Menu";
            }
            else
            {
                options = "[M] Menu";
            }

            padding = centerPadding(totalLength, options.length() + 19, 3);

            output << "┃" << setw(padding.paddingLeft) << left << "" << options;

            options = "[X] Change PIN Code";

            output << setw(padding.paddingRight) << left << "" << options;
            output << setw(padding.paddingRight) << right << "" << "┃";
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

            temp += addSpacingWithOutline(totalLength) + "┛";
        }
        else // Add spacings
        {
            output << "┃" << addSpacingWithoutOutline(1, totalLength - 3) << "┃";
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
}