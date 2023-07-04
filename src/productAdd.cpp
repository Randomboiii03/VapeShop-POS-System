#include "globalUtils.h"

using namespace std;

void productAdd()
{
    vector<Product> products = loadAllProducts();

    vector<string> navigation, newBanner, content, options;
    string temp, label, labelRow, name, brand, category, price, stocks;

    int bannerWidth, maxWidth, maxHeight, maxLength, optListWidth = 0, spaceContent = 8, padDetails = 0, minus = 0;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    navigation = navAdmin;
    options = {"[1] Save", "[0] Cancel"};

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Add Product"); // Banner display function

    maxHeight = newBanner.size() + spaceContent + 6; // Max height

    padding = centerPadding(maxHeight - newBanner.size(), spaceContent, 2);

    for (int i = 0; i < padding.paddingLeft; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    spaceContent = padding.paddingRight; // Number of spaces between content and options

    label = "Name: ";
    maxLength = getMaxLengthProduct(loadAllProducts(), 2, "");

    padding = centerPadding(maxWidth, label.length() + maxLength, 2);
    padDetails = padding.paddingLeft;

    labelRow = olVLine() + addNRepeat(" ", padDetails) + label + addNRepeat(" ", padding.paddingRight + maxLength) + olVLine();

    content.push_back(labelRow);

    temp = "Brand: ";

    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Category: ";

    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Price: ₱ ";

    padding = centerPadding(maxWidth, temp.length() - 2, 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    temp = "Stock/s: ";

    padding = centerPadding(maxWidth, temp.length(), 2);
    minus = splitString(temp, ':')[0].length() - label.length() + 2;

    content.push_back(olVLine() + addNRepeat(" ", padDetails - minus) + temp + addNRepeat(" ", (padding.paddingLeft - padDetails) + padding.paddingRight + minus) + olVLine());

    for (int i = 0; i < spaceContent; i++) // Space between enter pin code and options
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    content.push_back(olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider());

    for (string opt : options) // Option list width
    {
        optListWidth += opt.length();
    }

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

    cin.ignore();

    setInputPos(labelRow, maxWidth, newBanner.size() + 3, padDetails, label);
    getline(cin, name);

    setInputPos(labelRow, maxWidth, newBanner.size() + 4, padDetails, label);
    getline(cin, brand);

    setInputPos(labelRow, maxWidth, newBanner.size() + 5, padDetails, label);
    getline(cin, category);

    setInputPos(labelRow, maxWidth, newBanner.size() + 6, padDetails, label + "   ");
    cin >> price;

    setInputPos(labelRow, maxWidth, newBanner.size() + 7, padDetails, label);
    cin >> stocks;

    while (true)
    {
        char ch = getch();

        if (ch == '1')
        {
            try
            {
                if (stof(price) > 0 && stoi(stocks) > 0)
                {
                    int productID = 0;

                    for (int i = 0; i < products.size(); i++)
                    {
                        productID = max(productID, products[i].productID);
                    }

                    Product product = {productID + 1, checkCategory(category), brand, name, stof(price), stoi(stocks), 1};

                    products.push_back(product);
                    saveProducts(products);

                    temp = "Product added successfully!";
                    centerText(temp, temp.length());

                    categories = getCategories();

                    cin.ignore();

                    Sleep(2000);
                    productDisplay();
                }
                else
                {
                    temp = "Invalid input. Please enter a valid product details.";
                    centerText(temp, temp.length());

                    Sleep(2000);
                    productAdd();
                }
            }
            catch (const exception &) // Catch error
            {
                temp = "Invalid input. Please enter a valid product details.";
                centerText(temp, temp.length());

                Sleep(2000);
                productAdd();
            }
        }
        else if (ch == '0')
        {
            productDisplay();
        }
    }
}