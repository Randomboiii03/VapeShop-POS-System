#include "globalUtils.h"

using namespace std;

void productDisplay(string category)
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

    if (accountType == "User")
    {
        navigation = sideNavUser;

        columnName = {"No", "Brand", "Product Name", "Price"};
        maxLengths = {getMaxLengthProduct(products, 0, columnName[0]),
                      getMaxLengthProduct(products, 2, columnName[1]),
                      getMaxLengthProduct(products, 3, columnName[2]),
                      getMaxLengthProduct(products, 5, columnName[3])};
    }
    else if (accountType == "Admin")
    {
        navigation = sideNavAdmin;

        columnName = {"No", "Brand", "Product Name", "Price", "Stock", "Status"};
        maxLengths = {getMaxLengthProduct(products, 1, columnName[0]),
                      getMaxLengthProduct(products, 2, columnName[1]),
                      getMaxLengthProduct(products, 3, columnName[2]),
                      getMaxLengthProduct(products, 5, columnName[3]),
                      getMaxLengthProduct(products, 6, columnName[4]),
                      getMaxLengthProduct(products, 7, columnName[5])};
    }

    sideNav = navigation.size();

    for (auto &maxLength : maxLengths) // Total the width w/o menu
    {
        totalLength += maxLength;
    }

    bannerSize = banner[1].length();

    totalLength = max(static_cast<int>(bannerSize + 10), static_cast<int>(totalLength + ((maxLengths.size() * additionalDividerWidth) * 2))) + 3; // Compare width of banner and content

    maxSizeHeight = max(sideNav, (banner.size() + products.size()) + 5) + 2; // Compare height of sideNav and (banner + content)

    padding = centerPadding(static_cast<int>(maxSizeHeight) - 2, static_cast<int>(sideNav), 2); // Get left and right padding

    compiledSideNav = navigationDisplay(navigation, maxSizeHeight, sideNav, padding.paddingLeft); // Compile side navigation

    for (size_t i = 0; i <= banner.size(); i++) // Compile banner
    {
        temp = bannerDisplay(i, bannerSize, totalLength, category); // Compile banner
        compiledBanner.push_back(temp);
    }

    adj = compiledBanner.size();

    for (size_t i = adj; i < maxSizeHeight; i++) // Compile content
    {
        temp = "";

        if (i == adj || i == maxSizeHeight - 3 || i == adj + 2) // Add divider between title and PIN code, and between PIN code and options
        {
            temp += "┣" + addSpacingWithOutline(totalLength) + "┫";
        }
        else if (i == adj + 1) // Add header
        {
            for (size_t j = 0; j < columnName.size(); j++)
            {
                padding = centerPadding(maxLengths[j] + (additionalDividerWidth * 2), columnName[j].length(), 2);

                output << "┃" << setw(padding.paddingLeft) << left << "" << columnName[j] << setw(padding.paddingRight) << left << "";
            }

            output << "┃";
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

            padding = centerPadding(totalLength, options.length() + 36, 4);

            output << "┃" << setw(padding.paddingLeft) << left << "" << options;

            options = "[V] View Product";
            output << setw(padding.paddingRight) << right << "" << options;

            options = "[⇦ ⇨ ] Next Category";
            output << setw(padding.paddingRight) << right << "" << options;
            output << setw(padding.paddingRight) << right << ""
                   << "┃";
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
            if (i - 13 < products.size())
            {
                padding = centerPadding(maxLengths[0] + (additionalDividerWidth * 2), to_string(static_cast<int>(i - 13)).length(), 2);
                output << "┃" << setw(padding.paddingLeft) << left << "" << to_string(static_cast<int>(i - 13)) << setw(padding.paddingRight) << left << "";

                padding = centerPadding(maxLengths[1] + (additionalDividerWidth * 2), products[i - 13].brandName.length(), 2);
                output << "┃" << setw(padding.paddingLeft) << left << "" << products[i - 13].brandName << setw(padding.paddingRight) << left << "";

                padding = centerPadding(maxLengths[2] + (additionalDividerWidth * 2), products[i - 13].productName.length(), 2);
                output << "┃" << setw(padding.paddingLeft) << left << "" << products[i - 13].productName << setw(padding.paddingRight) << left << "";

                // cout << maxLengths[3] + (additionalDividerWidth * 2) << "-" << to_string(products[i - 13].price).length() << endl;

                ostringstream oss;
                oss << fixed << setprecision(2) << products[i - 13].price;

                padding = centerPadding(maxLengths[3] + (additionalDividerWidth * 2), oss.str().length() + 2, 2);
                output << "┃" << setw(padding.paddingLeft) << left << ""
                       << "₱ " << oss.str() << setw(padding.paddingRight) << left << ""
                       << "┃";
            }
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

    int count = 0;

    while (true) // Menus
    {
        char ch = getch();

        if (ch == 'm' && !isOpen) // Open menu
        {
            isOpen = true;
            productDisplay(category);
        }
        else if (ch == 27) // Close menu
        {
            if (isOpen)
            {
                isOpen = false;
                productDisplay(category);
            }
            else
            {
                count++;

                if(count > 10) {
                    pinCodeLogin();
                }
            }
        }
        else if (ch == 77) // Right
        {
            isOpen = false;
            nextCateg = (nextCateg + 1) % categories.size();
            productDisplay(categories[nextCateg]);
        }
        else if (ch == 75) // Left
        {
            isOpen = false;
            nextCateg = (nextCateg - 1 + categories.size()) % categories.size();
            productDisplay(categories[nextCateg]);
        }
        else if (ch == 'v') // View product
        {
            isOpen = false;
            // HELP
        }
        else
        {
            globalMenu(ch);
        }
    }
}