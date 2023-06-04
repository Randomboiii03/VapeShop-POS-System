#include "globalUtils.h"

using namespace std;

void productView(int prodIndex)
{
    // vector<Product> products = loadProductsByCategory(categories[nextCateg]);

    // vector<string> navigation, compiledSideNav, compiledBanner, compiledContent, columnName;
    // vector<int> maxLengths;

    // int totalLength = 0, adj, additionalDividerWidth = 3, bannerSize, infoSize;
    // size_t sideNav, maxSizeHeight, spacingMenu;

    // ostringstream output;
    // string temp, pin, options;

    // Padding padding;

    // system("cls");
    // SetConsoleOutputCP(CP_UTF8);

    // if (accountType == "User")
    // {
    //     navigation = navUser;
    // }
    // else if (accountType == "Admin")
    // {
    //     navigation = navAdmin;
    // }

    // sideNav = navigation.size();

    // totalLength = banner[1].length() + 10; // Total size of content w/o side navigation

    // maxSizeHeight = max(sideNav, banner.size()) + 11; // Compare height of side navigation and (banner + accounts)

    // padding = centerPadding(static_cast<int>(maxSizeHeight) - 2, static_cast<int>(sideNav), 2); // Get left and right padding

    // bannerSize = banner[1].length();

    // compiledSideNav = navigationDisplay(navigation, maxSizeHeight, sideNav, padding.paddingLeft); // Compile side navigation

    // for (size_t i = 0; i <= banner.size(); i++) // Compile banner
    // {
    //     temp = bannerDisplay(i, bannerSize, totalLength, category); // Compile banner
    //     compiledBanner.push_back(temp);
    // }

    // adj = compiledBanner.size();

    // for (size_t i = adj; i < maxSizeHeight; i++) // Compile content
    // {
    //     temp = "";

    //     if (i == adj || i == maxSizeHeight - 3) // Add divider between title and PIN code, and between PIN code and options
    //     {
    //         temp += "┣" + addSpacingWithOutline(totalLength) + "┫";
    //     }
    //     else if (i == adj + 5)
    //     {
    //         padding = centerPadding(totalLength, products[prodIndex].productName.length() + 13, 2);
    //         infoSize = padding.paddingLeft;

    //         output << "┃" << setw(padding.paddingLeft) << left << ""
    //                << "Product Name:" << products[prodIndex].productName
    //                << setw(padding.paddingRight) << right << ""
    //                << "┃";
    //     }
    //     else if (i == adj + 6)
    //     {
    //         output << "┃" << setw(infoSize + 2) << left << ""
    //                << "Brand Name:" << products[prodIndex].brandName
    //                << setw((totalLength - infoSize) - (products[prodIndex].brandName.length() + 13)) << right << ""
    //                << "┃";
    //     }
    //     else if (i == adj + 7)
    //     {
    //         ostringstream oss;
    //         oss << fixed << setprecision(2) << products[i - 13].price; // Add two decimal into the price

    //         output << "┃" << setw(infoSize + 7) << left << ""
    //                << "Price: ₱ " << oss.str()
    //                << setw((totalLength - infoSize) - (oss.str().length() + 16)) << right << ""
    //                << "┃";
    //     }
    //     else if (i == adj + 8)
    //     {
    //         output << "┃" << setw(infoSize + 7) << left << ""
    //                << "Stock: " << to_string(products[prodIndex].stock)
    //                << setw((totalLength - infoSize) - (to_string(products[prodIndex].stock).length() + 14)) << right << ""
    //                << "┃";
    //     }
    //     else if (i == adj + 9)
    //     {
    //         string status = products[i - 13].isAvailable ? "Available" : "Not Available";

    //         output << "┃" << setw(infoSize + 6) << left << ""
    //                << "Status: " << status
    //                << setw((totalLength - infoSize) - (status.length() + 14)) << right << ""
    //                << "┃";
    //     }
    //     else if (i == maxSizeHeight - 2) // Add options
    //     {
    //         if (isOpen)
    //         {
    //             options = "[Esc] Close Menu";
    //         }
    //         else
    //         {
    //             options = "[M] Menu";
    //         }

    //         if (accountType == "User")
    //         {
    //             padding = centerPadding(totalLength, options.length() + 11 + 15, 4);

    //             output << "┃" << setw(padding.paddingLeft) << left << "" << options;

    //             options = "[B] Buy Now";
    //             output << setw(padding.paddingRight) << left << "" << options;

    //             options = "[A] Add to Cart";
    //             output << setw(padding.paddingRight) << left << "" << options;

    //             output << setw(padding.paddingRight) << right << ""
    //                    << "┃";
    //         }
    //         else if (accountType == "Admin")
    //         {
    //             padding = centerPadding(totalLength, options.length() + 16 + 18, 4);

    //             output << "┃" << setw(padding.paddingLeft) << left << "" << options;

    //             options = "[E] Edit Product";
    //             output << setw(padding.paddingRight) << left << "" << options;

    //             options = "[D] Delete Product";
    //             output << setw(padding.paddingRight) << left << "" << options;

    //             output << setw(padding.paddingRight) << right << ""
    //                    << "┃";
    //         }
    //     }
    //     else if (i == maxSizeHeight - 1) // Add horizontal outline for bottom of content
    //     {
    //         if (isOpen)
    //         {
    //             temp += "┻";
    //         }
    //         else
    //         {
    //             temp += "┗";
    //         }

    //         temp += addSpacingWithOutline(totalLength) + "┛";
    //     }
    //     else // Add spacings
    //     {
    //         output << "┃" << addSpacingWithoutOutline(1, totalLength - 3) << "┃";
    //     }

    //     if (temp == "")
    //     {
    //         temp = output.str();
    //         output = ostringstream();
    //     }

    //     compiledContent.push_back(temp);
    // }

    // // Display the whole UI
    // for (size_t i = 0; i < maxSizeHeight; i++)
    // {
    //     if (isOpen)
    //     {
    //         cout << compiledSideNav[i]; // Display sideNav
    //     }

    //     if (i < compiledBanner.size())
    //     {
    //         cout << compiledBanner[i]; // Display banner
    //     }
    //     else
    //     {
    //         cout << compiledContent[i - adj]; // Display content (header, data and options)
    //     }

    //     cout << endl;
    // }

    // while (true) // Menus
    // {
    //     char ch = getch();

    //     if (ch == 'm' && !isOpen) // Open menu
    //     {
    //         isOpen = true;
    //         productView(category, prodIndex);
    //     }
    //     else if (ch == 27) // Close menu
    //     {
    //         isOpen = false;
    //         productView(category, prodIndex);
    //     }
    //     else if (accountType == "User")
    //     {
    //         if (ch == 'a')
    //         {
    //             // Add to cart
    //         }
    //         else if (ch == 'b')
    //         {
    //             // Buy now
    //         }
    //     }
    //     else if (accountType == "Admin")
    //     {
    //         if (ch == 'e')
    //         {
    //             // Edit product
    //         }
    //         else if (ch == 'd')
    //         {
    //             // Delete product
    //         }
    //     }
    //     else
    //     {
    //         globalMenu(ch);
    //     }
    // }
}