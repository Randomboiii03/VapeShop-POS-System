#include "headers.h"

using namespace std;

void showAccounts() {

    // Read txt file everytime function called/loaded
    vector<Account> admins = readFromFile("accounts/admins.txt");
    vector<Account> users = readFromFile("accounts/users.txt");

    vector<Account> accounts;
    vector<int> maxLengths;

    vector<string> navigation, compiledSideNav, compiledBanner, compiledContent;

    int totalLength = 0, adj, additionalDividerWidth = 6, endSpacing, startSpacing, num;
    size_t sideNav, maxSizeHeight, spacingMenu;

    string temp;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if(accountType == "Super Admin") {
        navigation = sideNavSuperAdmin;

        totalLength++;

        // Compile both admin and user accounts into one vector
        accounts.insert(accounts.end(), admins.begin(), admins.end());
        accounts.insert(accounts.end(), users.begin(), users.end());

        maxLengths = {getMaxLengthAcc(accounts, additionalDividerWidth, 0), getMaxLengthAcc(accounts, additionalDividerWidth, 1), getMaxLengthAcc(accounts, additionalDividerWidth, 2), getMaxLengthAcc(accounts, additionalDividerWidth, 3), getMaxLengthAcc(accounts, additionalDividerWidth, 4)};

    } else if (accountType == "Admin") {
        navigation = sideNavAdmin;

        accounts = users;

        additionalDividerWidth += 3;

        // Doesn't include accountType in displaying
        maxLengths = {getMaxLengthAcc(accounts, additionalDividerWidth, 0), getMaxLengthAcc(accounts, additionalDividerWidth, 2), getMaxLengthAcc(accounts, additionalDividerWidth, 3), getMaxLengthAcc(accounts, additionalDividerWidth, 4)};
    }

    sideNav = navigation.size();
    
    for (auto& maxLength : maxLengths) { // Total the width w/o menu
        totalLength += maxLength;
    }
    
    // Comparing width of banner and content)
    totalLength = max(static_cast<int>(banner[1].length() + 10), static_cast<int>(totalLength + (maxLengths.size() * additionalDividerWidth))) + 3; 
    
    maxSizeHeight = max(sideNav, (banner.size() + accounts.size()) + 5) + 11; // Comparing height of sideNav and (banner + accounts)

    spacingMenu = ((maxSizeHeight - 2) - sideNav); // Total spacing for sideNav

    spacingMenu = (spacingMenu / 2) + (spacingMenu % 2); // Half of spacing for sideNav
    
    // Compile newSideNav
    for (size_t i = 0; i < maxSizeHeight; i++) {

        if (i == 0) { // Compile top outline
            compiledSideNav.push_back("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");

        } else if (i - spacingMenu - 1 < sideNav) { // Compile sideNav
            compiledSideNav.push_back(navigation[i - spacingMenu - 1]);

        } else if (i == maxSizeHeight - 1) { // Compile bottom outline
            compiledSideNav.push_back("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");

        } else { // Compile spacing for sideNav < content
            compiledSideNav.push_back("┃                                               ");
        }
    }

    // Compile newBanner
    for (size_t i = 0; i <= banner.size(); i++) {

        ostringstream output;
        string temp = "";

        endSpacing = 0, startSpacing = 0;

        int bannerSize = banner[1].length();

        if (i <= banner.size()) {
            if (i == banner.size()) { // Get new bannerSize for title
                temp = "PROFILE";
                bannerSize = temp.length();
                temp = "";
            } 

            endSpacing = (totalLength - bannerSize) / 2 ;
            startSpacing = endSpacing + ((totalLength - bannerSize) % 2);

            if (i == 0 && isOpen) { // Add custom outline when menu isOpen
                temp += "┳";

            } else if (i == 0 && !isOpen) { // Add corner outline when menu !isOpen
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
                    output << "PROFILE";

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

        compiledBanner.push_back(temp);
    }

    adj = compiledBanner.size();

    // Compile content
    for (size_t i = adj; i < maxSizeHeight; i++) {

        ostringstream output;
        string temp = "";

        if (i == adj || i == adj + 2 || i == maxSizeHeight - 4) { // Add divider for header and between data and options
            temp += "┣";

            for (size_t j = 0; j < maxLengths.size(); j++) {

                for (size_t k = 0; k < maxLengths[j] + additionalDividerWidth; k++) {
                    temp += "━";
                }

                if (j != maxLengths.size() - 1 && i == adj) { // For top header
                    temp += "┳";

                } else if (j != maxLengths.size() - 1 && i == adj + 2) { // For bottom header
                    temp += "╋";

                } else if (j != maxLengths.size() - 1 && i == maxSizeHeight - 4) { // For between data and options
                    temp += "┻";
                }
            }

            temp += "┫";

        } else if (i < maxSizeHeight - 4) { // Add data and header
            int a = 0;

            if (i == adj + 1) { // Add header
                output << "┃" << setw(additionalDividerWidth) << right << "";

                output << setw(maxLengths[a]) << left << "No." << "┃" << setw(additionalDividerWidth) << right << "";
                a++;
            
                if (accountType == "Super Admin") {
                    output << setw(maxLengths[a]) << left << "Account Type" << "┃" << setw(additionalDividerWidth) << right << "";
                    a++;
                }

                output << setw(maxLengths[a]) << left << "Username" << "┃" << setw(additionalDividerWidth) << right << "";
                a++;
                output << setw(maxLengths[a]) << left << "Password" << "┃" << setw(additionalDividerWidth) << right << "";
                a++;
                output << setw(maxLengths[a]) << left << "Status" << "┃";

            } else if (i - (adj + 3) < accounts.size()) { // Add accounts
                output << "┃" << setw(additionalDividerWidth) << right << "";
                
                output << setw(maxLengths[a]) << left << to_string(i - (adj + 3)) << "┃" << setw(additionalDividerWidth) << right << "";
                a++;

                if (accountType == "Super Admin") {                
                    output << setw(maxLengths[a]) << left << accounts[i - (adj + 3)].accountType << "┃" << setw(additionalDividerWidth) << right << "";
                    a++;
                }

                output << setw(maxLengths[a]) << left << accounts[i - (adj + 3)].username << "┃" << setw(additionalDividerWidth) << right << "";
                a++;
                output << setw(maxLengths[a]) << left << accounts[i - (adj + 3)].password << "┃" << setw(additionalDividerWidth) << right << "";
                a++;
                output << setw(maxLengths[a]) << left << (accounts[i - (adj + 3)].isActive ? "Active" : "Banned/Disabled") << "┃";

            } else { // Add when empty or no account to add
                for (size_t j = 0; j < maxLengths.size(); j++) {
                    output << setw(maxLengths[j] + additionalDividerWidth + 3) << left << "┃";
                }

                output << "┃";
            }

        } else if (i < maxSizeHeight - 1) { // Add options
            string options = "";

            if (i == maxSizeHeight - 3 && isOpen) { // Row one, open nav options
                options = "[Esc] Close Menu        [Q] Search        [+] Add Account        [D] Delete Account";

            } else if (i == maxSizeHeight - 3 && !isOpen) { // Row one, close nav options
                options = "[M] Menu        [Q] Search        [+] Add Account        [D] Delete Account";

            } else { // Row two options
                options = "[U] Edit Username        [X] Edit Password        [K] Edit Status";
            }

            endSpacing = (totalLength - options.length()) / 2;
            startSpacing = endSpacing + (totalLength - options.length()) % 2;

            output << setw(startSpacing + 3) << left << "┃" << options;
            output << setw(endSpacing + 3) << right  << "┃";

        } else { // Add horizontal outline for bottom of content
            if (isOpen) {
                temp += "┻";
            } else {
                temp += "┗";
            }

            for (size_t j = 0; j < totalLength; j++) {
                temp += "━";
            }

            temp += "┛";
        }
        
        if (temp == "") {
            temp = output.str();
            output = ostringstream();
        }

        compiledContent.push_back(temp);
    }

    // Print the whole function
    for (size_t i = 0; i < maxSizeHeight; i++) {  

        if (isOpen) {
            cout << compiledSideNav[i]; // Print sideNav
        }

        if (i < compiledBanner.size()) {
            cout << compiledBanner[i]; // Print banner

        } else {
            cout << compiledContent[i - adj]; // Print content (header, data and options)
        }

        cout << endl;
    }

    while (true) { // Menus

        char ch = getch();

        try {

            if (ch == 'm' && !isOpen) { // Open menu
                isOpen = true;
                showAccounts();

            } else if (ch == 27 && isOpen) { // Close menu
                isOpen = false;
                showAccounts();

            } else if (ch == 'q') {
                // searchAccount();

            } else if (ch == '+') {
                // addAccount();

            } else if (ch == 'u' || ch == 'x' || ch == 'k' || ch == 'd') {
                int spacing = (totalLength + 3) / 2; // Spacing before entering credentials for login

                cout << setw(spacing) << left << "" << "Choose no.: ";
                cin >> temp;

                num = stoi(temp);

                isOpen = false;

                if (num > accounts.size() || num < 0) { // Not in range of accounts, return error message
                    temp = "Invalid input. Please enter a valid integer.";

                    endSpacing = (totalLength - temp.length()) / 2 ;
                    startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

                    cout << setw(startSpacing + 3) << left << "" << temp << endl;

                    Sleep(2000);
                    showAccounts();
                    
                } else if (ch == 'u') { // Edit username
                    editUsername(accounts[num].accountNumber, "showAccounts");

                } else if (ch == 'x') { // Edit password
                    editPassword(accounts[num].accountNumber, "showAccounts");

                } else if (ch == 'k') { // Edit status
                    // editStatus(accounts[num].accountNumber);

                } else if (ch == 'd') { // Delete account
                    // deleteAccount(accounts[num].accountNumber);
                }
                
            } else {
                menus(ch);
            }

        } catch (const exception&) { // Not a integer, catch error
            temp = "Invalid input. Please enter a valid integer.";

            endSpacing = (totalLength - temp.length()) / 2 ;
            startSpacing = endSpacing + ((totalLength - temp.length()) % 2);

            cout << setw(startSpacing + 3) << left << "" << temp << endl;

            Sleep(2000);
            showAccounts();
        }
    }
}