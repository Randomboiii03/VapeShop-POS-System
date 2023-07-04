#include "globalUtils.h"

using namespace std;

void pinCodeEditor()
{
    vector<Account> accounts;

    vector<string> newBanner, content, labels, labelRows, options;
    string oldPincode, newPinCode, confirmPincode, temp;

    vector<int> padY;
    int bannerWidth, maxWidth, optListWidth = 0, maxHeight, add = 10;

    boolean isValid = false;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    bannerWidth = banner[0].length() + 10; // Banner width

    maxWidth = bannerWidth; // Max width

    newBanner = bannerDisplay(maxWidth, bannerWidth, "Change PIN Code"); // Banner display

    for (int i = 0; i < 3; i++) // Space between banner and content
    {
        content.push_back(olVLine() + addNRepeat(" ", maxWidth) + olVLine());
    }

    labels = {"Old Pin Code: ", "New Pin Code: ", "Confirm Pin Code: "};

    for (int i = 0; i < labels.size(); i++)
    {
        if (i == labels.size() - 1)
        {
            add += 4;
        }

        padding = centerPadding(maxWidth, labels[i].length() + add, 2);
        padY.push_back(padding.paddingLeft);

        labelRows.push_back(olVLine() + addNRepeat(" ", padY[i]) + labels[i] + addNRepeat(" ", padding.paddingRight + add) + olVLine());
        content.push_back(labelRows[i]);
    }

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

    for (int i = 0; i < labels.size(); i++)
    {
        setInputPos(labelRows[i], maxWidth, 14 + i, padY[i], labels[i]); // Set input position
        
        switch (i)
        {
        case 0:
            cin >> oldPincode;
            break;
        case 1:
            cin >> newPinCode;
            break;
        case 2:
            cin >> confirmPincode;
            break;
        default:
            break;
        }
    }

    char ch = getch();

    try
    {
        if (ch == '1') // User submit to login
        {
            // Check if PIN code is valid
            stoi(oldPincode);
            stoi(newPinCode);
            stoi(confirmPincode);

            if (oldPincode != admin[0].pinCode)
            {
                temp = "Old PIN code is incorrect. PIN code not changed.";
            }
            else if (oldPincode == newPinCode)
            {
                temp = "PIN code is already used. PIN code not changed.";
            }
            else if (newPinCode != confirmPincode)
            {
                temp = "New PIN code and confirmation do not match. PIN code not changed.";
            }
            else if (newPinCode.length() != 6)
            {
                temp = "PIN code must be 6 digits long.";
            }
            else
            {
                isValid = true;
                temp = "PIN code changed successfully.";

                changePinCode(newPinCode);
            }

            centerText(temp, temp.length());
            Sleep(2000);

            if (isValid) // Login
            {
                pinCodeDisplay();
            }
            else
            {
                tries++;

                if (tries >= 5)
                {
                    temp = "Maximum login attempts reached. Please wait for one hour before trying again.";
                    centerText(temp, temp.length());

                    saveExpectedTime(calculateExpectedTime()); // Save the expected time after one hour of current time

                    Sleep(2000);
                    pinCodeDisplay();
                }
                else
                {
                    pinCodeEditor();
                }
            }
        }
        else // Cancel editing
        {
            pinCodeDisplay();
        }
    }
    catch (const exception &) // Catch error
    {
        temp = "Invalid input. Please enter a valid PIN code.";
        centerText(temp, temp.length());

        Sleep(2000);
        pinCodeDisplay();
    }
}