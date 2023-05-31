#include "globalUtils.h"

using namespace std;

void productDisplay(string category)
{
    vector<Product> products = loadProductsByCategory(category);

    vector<string> navigation, compiledSideNav, compiledBanner, compiledContent, columnName;
    vector<int> maxLengths;

    int totalLength = 0, adj, additionalDividerWidth = 4, num, bannerSize, navSize;
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

        additionalDividerWidth += 2;
    }
    else if (accountType == "Admin")
    {
        navigation = sideNavAdmin;

        columnName = {"No", "Brand", "Product Name", "Price", "Stock", "Status"};
        maxLengths = {getMaxLengthProduct(products, 0, columnName[0]),
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

    // Compare width of banner and content
    totalLength = max(static_cast<int>(bannerSize + 10), static_cast<int>(totalLength + ((maxLengths.size() * additionalDividerWidth) * 2)));

    maxSizeHeight = max(sideNav, (banner.size() + products.size()) + 5) + 2; // Compare height of sideNav and (banner + content)

    padding = centerPadding(static_cast<int>(maxSizeHeight) - 2, static_cast<int>(sideNav), 2); // Get left and right padding

    navSize = navigation[2].length();

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
                num = 0;

                if (j > 0)
                {
                    num = 1;
                }

                padding = centerPadding(maxLengths[j] + (additionalDividerWidth * 2) - num, columnName[j].length(), 2);

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
                // Compile by product index
                padding = centerPadding(maxLengths[0] + (additionalDividerWidth * 2), to_string(static_cast<int>(i - 13)).length(), 2);
                output << "┃" << setw(padding.paddingLeft) << left << "" << to_string(static_cast<int>(i - 13)) << setw(padding.paddingRight) << left << "";

                // Compile product brandName
                padding = centerPadding(maxLengths[1] + (additionalDividerWidth * 2) - 1, products[i - 13].brandName.length(), 2);
                output << "┃" << setw(padding.paddingLeft) << left << "" << products[i - 13].brandName << setw(padding.paddingRight) << left << "";

                // Compile product name
                padding = centerPadding(maxLengths[2] + (additionalDividerWidth * 2) - 1, products[i - 13].productName.length(), 2);
                output << "┃" << setw(padding.paddingLeft) << left << "" << products[i - 13].productName << setw(padding.paddingRight) << left << "";

                ostringstream oss;
                oss << fixed << setprecision(2) << products[i - 13].price; // Add two decimal into the price

                // Compile product price
                padding = centerPadding(maxLengths[3] + (additionalDividerWidth * 2) - 1, oss.str().length() + 2, 2);
                output << "┃" << setw(padding.paddingLeft) << left << ""
                       << "₱ " << oss.str() << setw(padding.paddingRight) << left << "";

                if (accountType == "Admin") // Compile stocks and status
                {
                    padding = centerPadding(maxLengths[4] + (additionalDividerWidth * 2) - 1, to_string(products[i - 13].stock).length(), 2);
                    output << "┃" << setw(padding.paddingLeft) << left << "" << to_string(products[i - 13].stock) << setw(padding.paddingRight) << left << "";

                    string status = products[i - 13].isAvailable ? "Available" : "Not Available"; // Set isAvailable into status

                    padding = centerPadding(maxLengths[5] + (additionalDividerWidth * 2) - 1, status.length(), 2);
                    output << "┃" << setw(padding.paddingLeft) << left << "" << status << setw(padding.paddingRight) << left << "";
                }

                output << "┃";
            }
            else // If there is no product to display
            {
                for (size_t j = 0; j < columnName.size(); j++)
                {
                    num = 0;

                    if (j > 0)
                    {
                        num = 1;
                    }

                    padding = centerPadding(maxLengths[j] + (additionalDividerWidth * 2) - num, 0, 2);
                    output << "┃" << setw(padding.paddingLeft) << left << "" << setw(padding.paddingRight) << left << "";
                }

                output << "┃";
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

    try
    {
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

                    if (count >= 10)
                    {
                        pinCodeLogin();
                    }
                }
            }
            else if (ch == 77) // Right
            {
                nextCateg = (nextCateg + 1) % categories.size();
                productDisplay(categories[nextCateg]);
            }
            else if (ch == 75) // Left
            {
                nextCateg = (nextCateg - 1 + categories.size()) % categories.size();
                productDisplay(categories[nextCateg]);
            }
            else if (ch == 'v') // View product
            {
                temp = "Choose product number: ";

                if (isOpen)
                {
                    padding = centerPadding(totalLength + navSize, temp.length(), 2);
                }
                else
                {
                    padding = centerPadding(totalLength, temp.length(),2);
                }
                
                cout << setw(padding.paddingLeft) << "" << temp;
                cin >> temp;

                productView(category, stoi(temp));
            }
            else
            {
                globalMenu(ch);
            }
        }
    }
    catch (const exception &) // Catch error
    {
        temp = "Invalid input. Please enter a valid PIN code.";

        padding = centerPadding(totalLength, temp.length(), 2);

        cout << setw(padding.paddingLeft + 3) << left << "" << temp << endl;

        Sleep(2000);
        productDisplay(category);
    }
}