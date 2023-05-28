#include "globalUtils.h"

using namespace std;

void pinCodeLogin()
{
    vector<Account> accounts;

    int totalLength = 0, bannerSize;

    string pinCode, temp;
    ostringstream output;

    bool isValid = false;

    Padding padding;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Compile both developer and admin accounts into one vector
    accounts.insert(accounts.end(), developer.begin(), developer.end());
    accounts.insert(accounts.end(), admin.begin(), admin.end());

    bannerSize = banner[1].length();
    totalLength = bannerSize + 10; // Total size of content w/o sideNav

    for (size_t i = 0; i <= banner.size(); i++)
    {
        temp = bannerDisplay(i, bannerSize, totalLength, "PIN CODE LOGIN"); // Display banner
        cout << temp << endl; // Display banner
    }

    totalLength = banner[1].length() + 10;

    cout << "┣";

    for (size_t j = 0; j < totalLength; j++) // Display outline after title
    {
        cout << "━";
    }

    cout << "┫" << endl;

    for (size_t i = 0; i < 3; i++) // Spacing
    {
        cout << setw(totalLength + 3) << left << ""
             << "" << endl;
    }

    int spacing = (totalLength + 3) / 3; // Spacing before entering credentials for login

    cout << setw(spacing) << left << ""
         << "Enter Pin Code: ";
    cin >> pinCode;

    for (size_t i = 0; i < 3; i++) // Spacing
    {
        cout << setw(totalLength + 3) << left << ""
             << "" << endl;
    }

    cout << "┣";

    for (size_t j = 0; j < totalLength; j++) // Display outline after inputs
    {
        cout << "━";
    }

    cout << "┫" << endl;

    temp = "[1] Submit";

    padding = centerPadding(totalLength, 20, 3);

    cout << setw(padding.paddingLeft + 3) << left << "┃" << temp;

    temp = "[0] Cancel";

    cout << setw(padding.paddingLeft + 3) << left << "" << temp;
    cout << setw(padding.paddingRight) << right << "┃" << endl;

    cout << "┗";

    for (size_t j = 0; j < totalLength; j++)
    {
        cout << "━";
    }

    cout << "┛" << endl;

    temp = "";

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

            padding = centerPadding(totalLength, temp.length(), 2);
            cout << setw(padding.paddingLeft + 3) << left << "" << temp;

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

                    padding = centerPadding(totalLength, temp.length(), 2);
                    cout << setw(padding.paddingLeft + 3) << left << "" << temp;

                    saveExpectedTime(calculateExpectedTime()); // Save the expected time after one hour of current time

                    Sleep(2000);
                    // Go back function
                }
                else
                {
                    pinCodeLogin();
                }
            }
        }
        else // Cancel
        {
            // Go back function
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