#include "globalUtils.h"

using namespace std;

void pinCodeEditor()
{
    // int totalLength = 0, bannerSize;

    // string oldPinCode, pinCode, newPinCode, temp;
    // bool isValid = false;

    // Padding padding;

    // system("cls");
    // SetConsoleOutputCP(CP_UTF8);

    // bannerSize = banner[1].length();
    // totalLength = bannerSize + 10; // Total size of content w/o sideNav
    
    // for (size_t i = 0; i <= banner.size(); i++)
    // {
    //     temp = bannerDisplay(i, bannerSize, totalLength, "CHANGE PIN CODE"); // Display banner
    //     cout << temp << endl;
    // }

    // totalLength = banner[1].length() + 10;

    // cout << "┣" << addSpacingWithOutline(totalLength) << "┫" << endl;

    // cout << addSpacingWithoutOutline(3, totalLength);

    // int spacing = (totalLength + 3) / 3; // Spacing before inputs

    // cout << setw(spacing) << left << "" << "Old Pin Code: ";
    // cin >> oldPinCode;

    // cout << setw(spacing) << left << "" << "New Pin Code: ";
    // cin >> pinCode;

    // cout << setw(spacing - 4) << left << "" << "Confirm Pin Code: ";
    // cin >> newPinCode;

    // cout << addSpacingWithoutOutline(3, totalLength); // Spacing without outline

    // cout << "┣" << addSpacingWithOutline(totalLength) << "┫" << endl;

    // temp = "[1] Submit";

    // padding = centerPadding(totalLength, 20, 3); // Get left and right padding

    // cout << setw(padding.paddingLeft + 3) << left << "┃" << temp;

    // temp = "[0] Cancel";

    // cout << setw(padding.paddingLeft + 3) << left << "" << temp;
    // cout << setw(padding.paddingRight) << right << "┃" << endl;

    // cout << "┗" << addSpacingWithOutline(totalLength) << "┛" << endl;

    // temp = "";

    // char ch = getch();

    // try
    // {
    //     if (ch == '1') // User submit to login
    //     {
    //         if (oldPinCode != admin[0].pinCode)
    //         {
    //             temp = "Old PIN code is incorrect. PIN code not changed.";
    //         }
    //         else if (oldPinCode != pinCode)
    //         {
    //             temp = "PIN code is already used. PIN code not changed.";
    //         }
    //         else if (pinCode != newPinCode)
    //         {
    //             temp = "New PIN code and confirmation do not match. PIN code not changed.";
    //         }
    //         else
    //         {
    //             isValid = true;
    //             temp = "PIN code changed successfully.";

    //             changePinCode(pinCode);
    //         }

    //         padding = centerPadding(totalLength, temp.length(), 2);

    //         cout << setw(padding.paddingLeft + 3) << left << "" << temp << endl;
    //         Sleep(2000);

    //         if (isValid) // Login
    //         {
    //             pinCodeDisplay();
    //         }
    //         else
    //         {
    //             tries++;

    //             if (tries >= 5)
    //             {
    //                 temp = "Maximum login attempts reached. Please wait for one hour before trying again.";

    //                 padding = centerPadding(totalLength, temp.length(), 2);
    //                 cout << setw(padding.paddingLeft + 3) << left << "" << temp;

    //                 saveExpectedTime(calculateExpectedTime()); // Save the expected time after one hour of current time

    //                 Sleep(2000);
    //                 pinCodeDisplay();
    //             }
    //             else 
    //             {
    //                 pinCodeEditor();
    //             }
                
    //         }
    //     }
    //     else // Cancel editing
    //     {
    //         pinCodeDisplay();
    //     }
    // }
    // catch (const exception &) // Catch error
    // {
    //     temp = "Invalid input. Please enter a valid PIN code.";

    //     padding = centerPadding(totalLength, temp.length(), 2);

    //     cout << setw(padding.paddingLeft + 3) << left << "" << temp << endl;

    //     Sleep(2000);
    //     pinCodeLogin();
    // }
}