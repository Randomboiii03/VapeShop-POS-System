#include "headers.h"

using namespace std;

void login()
{
    vector<Account> accounts;

    int totalLength = 0, bannerSize, endSpacing, startSpacing;

    string pinCode, temp;
    bool isValid = false;

    ostringstream output;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Compile both developer and admin accounts into one vector
    accounts.insert(accounts.end(), developer.begin(), developer.end());
    accounts.insert(accounts.end(), admin.begin(), admin.end());

    bannerSize = banner[1].length();
    totalLength = bannerSize + 10; // Total size of content w/o sideNav

    for (size_t i = 0; i <= banner.size(); i++)
    {
        temp = "";

        endSpacing = 0, startSpacing = 0;

        if (i <= banner.size())
        {
            if (i == banner.size()) // Get new bannerSize for title
            {
                temp = "LOGIN";
                bannerSize = temp.length();
            }

            endSpacing = (totalLength - bannerSize) / 2;
            startSpacing = endSpacing + ((totalLength - bannerSize) % 2);

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
                for (size_t j = 0; j < startSpacing; j++)
                {
                    temp += "━";
                }

                temp += banner[i];

                for (size_t j = 0; j < endSpacing; j++)
                {
                    temp += "━";
                }

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
                output << setw(startSpacing + 3) << left << "┃";

                if (i == banner.size())
                {
                    output << "LOGIN";
                }
                else
                {
                    output << banner[i];
                }

                output << setw(endSpacing + 3) << right << "┃";
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

    endSpacing = (totalLength - 20) / 3;
    startSpacing = endSpacing + ((totalLength - 20) % 3);

    cout << setw(startSpacing + 3) << left << "┃" << temp;

    temp = "[0] Cancel";

    cout << setw(startSpacing + 3) << left << "" << temp;
    cout << setw(endSpacing) << right << "┃" << endl;

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
            for (auto &account : accounts)
            {
                if (stoi(pinCode) == account.pinCode)
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

            endSpacing = (totalLength - temp.length()) / 2;
            startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

            cout << setw(startSpacing + 3) << left << "" << temp;

            Sleep(2000);

            if (isValid) // Login
            {
                if (accountType == "Developer")
                {
                    // Go to developer ui
                }
                else if (accountType == "Admin")
                {
                    // Go to admin ui
                }
            }
            else // Wrong PIN code
            {
                if (tries <= 5)
                {
                    // Go back
                }
                else
                {
                    login();
                }
            }
        }
        else // Cancel
        {
            // Go back
        }
    }
    catch (const exception &) // Not an integer, catch error
    {
        temp = "Invalid input. Please enter a valid integer.";

        endSpacing = (totalLength - temp.length()) / 2;
        startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

        cout << setw(startSpacing + 3) << left << "" << temp << endl;

        Sleep(2000);
        login();
    }
}