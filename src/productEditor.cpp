#include "globalUtils.h"

using namespace std;

void productEditor(int prodID, int editIndex)
{
    vector<Product> products = loadAllProducts();

    vector<string> newBanner, content, options, editOptions;
    string temp, label, labelRow, detail;

    int bannerWidth, maxWidth, maxHeight, maxLength, optListWidth = 0, spaceContent = 9, padDetails = 0, minus = 0, prodIndex = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    editOptions = {"Product Name", "Product Brand", "Product Category", "Product Price", "Product Stocks", "Product Status"};

    options = {"[E] Edit " + editOptions[editIndex], "[🔼🔽] Next", "[B] Back"};

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Edit Product"); // Banner display function

    maxHeight = newBanner.size() + spaceContent + 6; // Max height

    padding = centerPadding(maxHeight - newBanner.size(), spaceContent, 2);

    for (int i = 0; i < padding.paddingLeft; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    spaceContent = padding.paddingRight; // Number of spaces between content and options

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].productID == prodID)
        {
            label = "Name: ";
            temp = label + products[i].productName;

            padding = centerPadding(maxWidth, temp.length(), 2);
            padDetails = padding.paddingLeft;

            labelRow = olVLine() + addNRepeat(" ", padDetails) + temp + addNRepeat(" ", padding.paddingRight) + olVLine();

            content.push_back(labelRow);

            temp = "Brand: " + products[i].brandName;

            padding = centerPadding(maxWidth, temp.length(), 2);
            minus = splitString(temp, ':')[0].length() - label.length() + 2;

            content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

            temp = "Category: " + products[i].category;

            padding = centerPadding(maxWidth, temp.length(), 2);
            minus = splitString(temp, ':')[0].length() - label.length() + 2;

            content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

            temp = "Price: ₱ " + priceFormat(products[i].price);

            padding = centerPadding(maxWidth, temp.length() - 2, 2);
            minus = splitString(temp, ':')[0].length() - label.length() + 2;

            content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

            temp = "Stock/s: " + to_string(products[i].stock);

            padding = centerPadding(maxWidth, temp.length(), 2);
            minus = splitString(temp, ':')[0].length() - label.length() + 2;

            content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

            string status = products[i].isAvailable ? "Available" : "Not Available";
            temp = "Status: " + status;

            padding = centerPadding(maxWidth, temp.length(), 2);
            minus = splitString(temp, ':')[0].length() - label.length() + 2;

            content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

            prodIndex = i;

            break;
        }
    }

    for (int i = 0; i < spaceContent; i++) // Space between enter pin code and options
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    content.push_back(olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider());

    for (string opt : options) // Option list width
    {
        optListWidth += opt.length();
    }

    optListWidth -= 4;

    padding = centerPadding(maxWidth, optListWidth, options.size() + 1);
    temp = olVLine() + addNRepeat(" ", padding.paddingLeft);

    for (string opt : options)
    {
        temp += opt + addNRepeat(" ", padding.paddingRight);
    }

    temp += olVLine();

    content.push_back(temp); // Options display

    content.push_back(olBLCorner() + addNRepeat(olHLine(), maxWidth) + olBRCorner()); // Footer display

    for (int i = 0; i < maxHeight; i++)
    {
        temp = "";

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

    while (true)
    {
        char ch = getch();

        if (ch == 72) // Up
        {
            editIndex = (editIndex - 1 + 6) % 6;
            productEditor(prodID, editIndex);
        }
        else if (ch == 80) // Down
        {
            editIndex = (editIndex + 1) % 6;
            productEditor(prodID, editIndex);
        }
        else if (ch == 'b')
        {
            productView(prodIndex, products);
        }
        else if (ch == 'e')
        {
            if (editIndex < 5)
            {
                temp = "Enter New " + editOptions[editIndex] + ": ";
                centerText(temp, temp.length());

                setInputPos(temp, temp.length(), 0, -1, temp);
                cin >> detail;
            }
            else
            {
                temp = products[prodIndex].isAvailable ? "Not Available" : "Available";
                temp = "New " + editOptions[editIndex] + ": " + temp;

                centerText(temp, temp.length());
            }

            temp = "Are you sure you want to edit this product? [Y/N]";
            centerText(temp, temp.length());

            while (true)
            {
                char ch = getch();

                if (ch == 'y')
                {
                    try
                    {
                        switch (editIndex)
                        {
                        case 0:
                            products[prodIndex].productName = detail; // Edit product name
                            break;
                        case 1:
                            products[prodIndex].brandName = detail; // Edit product brand
                            break;
                        case 2:
                            products[prodIndex].category = checkCategory(detail); // Edit product category
                            break;
                        case 3:
                            if (stof(detail) < 0)
                            {
                                temp = "Invalid input. Please enter a valid product details.";
                                centerText(temp, temp.length());

                                Sleep(2000);
                                productView(prodIndex, products);
                            }

                            products[prodIndex].price = stof(detail); // Edit product price
                            break;
                        case 4:
                            if (stoi(detail) < 0)
                            {
                                temp = "Invalid input. Please enter a valid product details.";
                                centerText(temp, temp.length());

                                Sleep(2000);
                                productView(prodIndex, products);
                            }

                            products[prodIndex].stock = stoi(detail); // Edit product stock
                            break;
                        case 5:
                            if (products[prodIndex].isAvailable) // Edit product availability
                            {
                                products[prodIndex].isAvailable = false;
                            }
                            else
                            {
                                products[prodIndex].isAvailable = true;
                            }
                            break;
                        default:
                            break;
                        }

                        saveProducts(products);

                        productView(prodIndex, products);
                    }
                    catch (const exception &) // Catch error
                    {
                        temp = "Invalid input. Please enter a valid product details.";
                        centerText(temp, temp.length());

                        Sleep(2000);
                        productView(prodIndex, products);
                    }
                }
                else if (ch == 'n')
                {
                    productView(prodIndex, products);
                }
            }
        }
    }
}