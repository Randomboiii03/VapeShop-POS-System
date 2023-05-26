#include "headers.h"

using namespace std;

void editPassword(int accNumber, string function) {

    // Read txt file everytime function called/loaded
    vector<Account> admins = readFromFile("accounts/admins.txt");
    vector<Account> users = readFromFile("accounts/users.txt");

    vector<Account> accounts;

    int totalLength = 0, endSpacing, startSpacing;

    pair<string, string> credential = getCredentials(accNumber);

    string password, filename, temp;
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
                temp = "EDIT PASSWORD";
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
                    output << "EDIT PASSWORD";

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

    cout << setw(spacing) << left << "┃" << "Old Password: ";

    for (size_t j = 0; j < credential.second.length(); j++) {

        if (j == credential.second.length() - 1) { // Add last character of password
            cout << credential.second[j] << endl;
                        
        } else { // Add password as asterisks
            cout << '*';
        } 
    }
    
    cout << setw(spacing) << left << "┃" << "New Password: ";
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

    // User save changes to password
    if (ch == '1') {

        if (credential.second == password) { // If same password is inputted
            temp = "New password is the same as the current password.";

        } else if (!validatePassword(password)) { // If wrong format is inputted
            temp = "Invalid password. It should be at least 8 characters long and contain at least";

        } else {
            temp = "Password changed successfully!";
            isValid = true;
        }

        endSpacing = (totalLength - temp.length()) / 2 ;
        startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

        cout << setw(startSpacing + 3) << left << "" << temp << endl;

        if (!validatePassword(password)) { // Continuation of response
            cout << setw(startSpacing + 2) << left << "" << "one uppercase letter, one lowercase letter, one digit, and one special character.";
        }

        if (isValid) {

            for (auto& account : accounts) {
                if (accNumber == account.accountNumber) {
                    account.password = password;
                }
            }

            writeToFile(filename, accounts); // Save new password
        }

        Sleep(2000);
    } 

    if (function == "showProfile") {
        showProfile();

    } else if (function == "showAccounts") {
        showAccounts();
    }
}