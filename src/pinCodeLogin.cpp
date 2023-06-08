#include "globalUtils.h"

using namespace std;

void pinCodeLogin()
{
    vector<Account> accounts;

    vector<string> newBanner, content, options;
    string pinCode, temp, label, labelRow;

    int bannerWidth, maxWidth, optListWidth = 0, maxHeight, padY;

    bool isValid = false;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Compile both developer and admin accounts into one vector
    accounts.insert(accounts.end(), developer.begin(), developer.end());
    accounts.insert(accounts.end(), admin.begin(), admin.end());

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    newBanner = bannerDisplay(maxWidth, bannerWidth, "PIN Code Login"); // Banner display

    for (int i = 0; i < 3; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    label = "Enter Pin Code: ";
    padding = centerPadding(maxWidth, label.length() + 8, 2);
    padY = padding.paddingLeft;

    labelRow = olVLine() + addNRepeat(" ", padY) + label + addNRepeat(" ", padding.paddingRight + 8) + olVLine();

    // Enter pin code
    content.push_back(labelRow);

    for (int i = 0; i < 3; i++) // Space between enter pin code and options
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    content.push_back(olLVDivider() + addNRepeat(olHLine(), maxWidth) + olRVDivider());

    options = {"[1] Submit", "[0] Cancel"};

    for (string option : options) // Option list width
    {
        optListWidth += option.length();
    }

    padding = centerPadding(maxWidth, optListWidth, options.size() + 1);

    temp = olVLine() + addNRepeat(" ", padding.paddingLeft);

    for (string option : options)
    {
        temp += option + addNRepeat(" ", padding.paddingRight);
    }

    temp += olVLine();

    content.push_back(temp); // Options display

    content.push_back(olBLCorner() + addNRepeat(olHLine(), maxWidth) + olBRCorner()); // Footer display

    maxHeight = newBanner.size() + content.size();

    for (int i = 0; i < maxHeight; i++) // Content display
    {
        if (i < newBanner.size())
        {
            temp = newBanner[i];
        }
        else
        {
            temp = content[i - newBanner.size()];
        }

        centerText(temp, maxWidth);
    }

    setInputPos(labelRow, maxWidth, newBanner.size() + 3, padY, label); // Set input position
    cin >> pinCode;

    char ch = getch();

    try
    {
        if (ch == '1') // User submit to login
        {
            stoi(pinCode); // Check if integer

            for (auto &account : accounts)
            {
                if (pinCode == account.pinCode)
                {
                    isValid = true;
                    accountType = account.accountType;
                    temp = accountType + " successfully login!";
                    break;
                }
            }

            if (!isValid) // Wrong PIN code
            {
                temp = "Wrong PIN code!";
                tries++;
            }

            centerText(temp, temp.length());

            Sleep(2000);

            if (isValid) // Login
            {
                pinCodeDisplay();
            }
            else // Wrong PIN code
            {
                if (tries >= 5)
                {
                    temp = "Maximum login attempts reached. Please wait for one hour before trying again.";

                    centerText(temp, temp.length());

                    saveExpectedTime(calculateExpectedTime()); // Save the expected time after one hour of current time
                    Sleep(2000);
                    productDisplay();
                }
                else
                {
                    saveExpectedTime(calculateExpectedTime());
                    pinCodeLogin();
                }
            }
        }
        else if (ch == '0') // Cancel
        {
            productDisplay();
        }
        else
        {
            temp = "Invalid input. Please enter a valid PIN code.";
            centerText(temp, temp.length());

            Sleep(2000);
            pinCodeLogin();
        }
    }
    catch (const exception &) // Catch error
    {
        temp = "Invalid input. Please enter a valid PIN code.";
        centerText(temp, temp.length());

        Sleep(2000);
        pinCodeLogin();
    }
}