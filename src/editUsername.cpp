#include "headers.h"

using namespace std;

void editUsername(int accNumber, string function) {

    // Read txt file everytime function called/loaded
    vector<Account> admins = readFromFile("accounts/admins.txt");
    vector<Account> users = readFromFile("accounts/users.txt");

    vector<Account> accounts;

    int totalLength = 0, endSpacing, startSpacing;

    pair<string, string> credential = getCredentials(accNumber);

    string username, filename, temp;
    bool isValid = false;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Check accountType to find filename (database)
    if (getAccountType(accNumber) == "Admin") {
        accounts.insert(accounts.end(), admins.begin(), admins.end());
        filename = "accounts/admins.txt";

    } else if (getAccountType(accNumber) == "User") {
        accounts.insert(accounts.end(), users.begin(), users.end());
        filename = "accounts/users.txt";
    }

    totalLength = banner[1].length() + 10; // Total size of content w/o sideNav
    
    for (size_t i = 0; i <= banner.size(); i++) {

        ostringstream output;
        temp = "";

        endSpacing = 0, startSpacing = 0;

        int bannerSize = banner[1].length();

        if (i <= banner.size()) {
            if (i == banner.size()) { // Get new bannerSize for title
                temp = "EDIT USERNAME";
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
                    output << "EDIT USERNAME";

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

    cout << setw(spacing) << left << "┃" << "Old Username: ";
    cout << credential.first << endl;

    cout << setw(spacing) << left << "┃" << "New Username: ";
    cin >> username;

    // Spacing
    for (size_t i = 0; i < 3; i++) {
        cout << setw(totalLength + 3) << left << "┃" << "┃" << endl;
    }

    cout << "┣";

    for (size_t j = 0; j < totalLength; j++) { // Print outline after inputs
        cout << "━";
    }

    cout << "┫" << endl;

    temp = "[1] Save          [0] Cancel";

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

    // User save changes to username
    if (ch == '1') {

        if (credential.first == username) { // If same username is inputted
            temp = "New username is the same as the current username.";

        } else if (!validateUsername(username)) { // If wrong format is inputted
            temp = "Invalid username. It should be 3 to 16 characters long and ";

        } else if (!isUsernameAvailable(username)) { // If wrong format is inputted
            temp = "Username is not available. Please choose a different username.";

        } else {
            temp = "Username changed successfully!";
            isValid = true;
        }

        endSpacing = (totalLength - temp.length()) / 2 ;
        startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

        cout << setw(startSpacing + 3) << left << "" << temp << endl;

        if (!validateUsername(username)) { // Continuation of response
            cout << setw(startSpacing + 10) << left << "" << "may contain alphanumeric, underscore, or hyphen.";
        }

        if (isValid) {

            for (auto& account : accounts) {
                if (accNumber == account.accountNumber) {
                    account.username = username;
                }
            }
            
            writeToFile(filename, accounts); // Save new username
        }

        Sleep(2000);
    } 

    if (function == "showProfile") {
        showProfile();

    } else if (function == "showAccounts") {
        showAccounts();
    }
}