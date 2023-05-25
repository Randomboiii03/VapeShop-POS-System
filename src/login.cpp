#include "headers.h"

using namespace std;



void login() {
    
    // Read txt file everytime function called/loaded
    vector<Account> admins = readFromFile("accounts/admins.txt");
    vector<Account> users = readFromFile("accounts/users.txt");

    vector<Account> accounts;

    int totalLength = 0, endSpacing, startSpacing;

    string username, password, temp;
    bool isValid;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Compile both admin and user accounts into one vector
    accounts.insert(accounts.end(), superadmin.begin(), superadmin.end());
    accounts.insert(accounts.end(), admins.begin(), admins.end());
    accounts.insert(accounts.end(), users.begin(), users.end());

    totalLength = banner[1].length() + 10; // Total size of content w/o sideNav
    
    for (size_t i = 0; i <= banner.size(); i++) {

        ostringstream output;
        temp = "";

        endSpacing = 0, startSpacing = 0;

        int bannerSize = banner[1].length();

        if (i <= banner.size()) {
            if (i == banner.size()) { // Get new bannerSize for title
                temp = "LOGIN";
                bannerSize = temp.length();
                temp = "";
            } 

            endSpacing = (totalLength - bannerSize) / 2 ;
            startSpacing = endSpacing + ((totalLength - bannerSize) % 2);

            if (i == 0) { // Add corner outline when menu !isOpen
                temp += "┏";

            } else if (i == banner.size() - 1) { // Add custom vertical divider
                temp += "┣";
            }

            if (i == 0 || i == banner.size() - 1) { // Add additional horizontal outline before and after of banner

                for (size_t j = 0; j < startSpacing; j++) {
                    temp += "━";
                }

                temp += banner[i];

                for (size_t j = 0; j < endSpacing; j++) {
                    temp += "━";
                }

                if (i == 0) {
                    temp += "┓";

                } else {
                    temp += "┫";
                }

            } else { // Add spacing before and after of banner < totalLength of accounts, and title
                output << setw(startSpacing + 3) << left << "┃";

                if (i == banner.size()) {
                    output << "LOGIN";

                } else {
                    output << banner[i];
                }

                output << setw(endSpacing + 3) << right  << "┃"; 
            }
        }

        if (temp == "") {
            temp = output.str();
            output = ostringstream();
        }

        cout << temp << endl;
    }
    
    cout << "┣";

    for (size_t j = 0; j < totalLength; j++) { // Print outline after title
        cout << "━";
    }

    cout << "┫" << endl;

    // Spacing
    for (size_t i = 0; i < 3; i++) {
        cout << setw(totalLength + 3) << left << "┃" << "┃" << endl;
    }

    int spacing = (totalLength + 3) / 3; // Spacing before entering credentials for login

    cout << setw(spacing) << left << "┃" << "Username: ";
    cin >> username;


    cout << setw(spacing) << left << "┃" << "Password: ";
    cin >> password;

    // Spacing
    for (size_t i = 0; i < 3; i++) {
        cout << setw(totalLength + 3) << left << "┃" << "┃" << endl;
    }

    cout << "┣";

    for (size_t j = 0; j < totalLength; j++) { // Print outline after inputs
        cout << "━";
    }

    cout << "┫" << endl;

    temp = "[1] Submit          [0] Clear";

    endSpacing = (totalLength - temp.length()) / 2 ;
    startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

    cout << setw(startSpacing + 3) << left << "┃" << temp;
    cout << setw(endSpacing + 3) << right << "┃" << endl;

    cout << "┗";

    for (size_t j = 0; j < totalLength; j++) {
        cout << "━";
    }

    cout << "┛" << endl;

    temp = "";
    
    char ch = getch();

    // User submit to login
    if (ch == '1') {

        for (auto& account : accounts) {

            if (username == account.username && password == account.password) {
                if (!account.isActive) { // If account is banned/disabled
                    temp = "Account is banned/disabled";
                    break;

                } else { // Credentials match and active status
                    isValid = true;
                    accountNumber = account.accountNumber;
                    accountType = account.accountType;

                    temp = account.accountType + " successfully login!";
                    break;
                }
            }
        }

        if (!isValid && temp == "") { // No match credentials
            temp = "Wrong username or password!";
        }

        endSpacing = (totalLength - temp.length()) / 2 ;
        startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

        cout << setw(startSpacing + 3) << left << "" << temp;

        Sleep(2000);

        if (!isValid) { // No match credentials or account is banned/disabled
            login();

        } else {
            showProfile();
        }

    } else { // Clear inputs and go back to login
        login();
    }
}