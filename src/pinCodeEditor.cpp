#include "globalUtils.h"

using namespace std;

void pinCodeEditor()
{
    int totalLength = 0, bannerSize;

    string oldPinCode, pinCode, newPinCode, temp;
    bool isValid = false;

    ostringstream output;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    bannerSize = banner[1].length();
    totalLength = bannerSize + 10; // Total size of content w/o sideNav
    
    for (size_t i = 0; i <= banner.size(); i++)
    {
        temp = "";

        if (i <= banner.size())
        {
            if (i == banner.size()) // Get new bannerSize for title
            {
                temp = "CHANGE PIN CODE";
                bannerSize = temp.length();
                temp = "";
            }

            padding = centerPadding(totalLength, bannerSize, 2); // Get left and right padding

            if (i == 0) // Add corner outline when menu !isOpen
            {
                temp += "┏";
            }
            else if (i == banner.size() - 1) // Add custom vertical divider
            {
                temp += "┣";
            }

            if (i == 0 || i == banner.size() - 1) // Add additional horizontal outline before and after of banner
            {
                temp += addSpacingWithOutline(padding.paddingLeft) + banner[i] + addSpacingWithOutline(padding.paddingRight);

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
                output << setw(padding.paddingLeft + 3) << left << "┃";

                if (i == banner.size())
                {
                    output << "CHANGE PIN CODE";
                }
                else
                {
                    output << banner[i];
                }

                output << setw(padding.paddingRight + 3) << right << "┃";
            }
        }

        if (temp == "") // Compile non-outline
        {
            temp = output.str();
            output = ostringstream();
        }

        cout << temp << endl; // Display banner
    }

    totalLength = banner[1].length() + 10;

    cout << "┣" << addSpacingWithOutline(totalLength) << "┫" << endl;

    cout << addSpacingWithoutOutline(3, totalLength);

    int spacing = (totalLength + 3) / 3; // Spacing before entering credentials for login

    cout << setw(spacing) << left << "" << "Old Pin Code: ";
    cin >> oldPinCode;

    cout << setw(spacing) << left << "" << "New Pin Code: ";
    cin >> pinCode;

    cout << setw(spacing - 4) << left << "" << "Confirm Pin Code: ";
    cin >> newPinCode;

    cout << addSpacingWithoutOutline(3, totalLength); // Spacing without outline

    cout << "┣" << addSpacingWithOutline(totalLength) << "┫" << endl;

    temp = "[1] Submit";

    padding = centerPadding(totalLength, 20, 3); // Get left and right padding

    cout << setw(padding.paddingLeft + 3) << left << "┃" << temp;

    temp = "[0] Cancel";

    cout << setw(padding.paddingLeft + 3) << left << "" << temp;
    cout << setw(padding.paddingRight) << right << "┃" << endl;

    cout << "┗" << addSpacingWithOutline(totalLength) << "┛" << endl;

    temp = "";

    char ch = getch();

    try
    {
        if (ch == '1') // User submit to login
        {
            if (oldPinCode != admin[0].pinCode)
            {
                temp = "Old PIN code is incorrect. PIN code not changed.";
            }
            else if (pinCode != newPinCode)
            {
                temp = "New PIN code and confirmation do not match. PIN code not changed.";
            }
            else
            {
                isValid = true;
                temp = "PIN code changed successfully.";

                changePinCode(pinCode);
            }

            padding = centerPadding(totalLength, temp.length(), 2);

            cout << setw(padding.paddingLeft + 3) << left << "" << temp << endl;
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

                    padding = centerPadding(totalLength, temp.length(), 2);
                    cout << setw(padding.paddingLeft + 3) << left << "" << temp;

                    saveExpectedTime(calculateExpectedTime()); // Save the expected time after one hour of current time
                    Sleep(2000);
                }

                pinCodeEditor();
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

        padding = centerPadding(totalLength, temp.length(), 2);

        cout << setw(padding.paddingLeft + 3) << left << "" << temp << endl;

        Sleep(2000);
        pinCodeLogin();
    }
}