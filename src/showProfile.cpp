#include "headers.h"

using namespace std;

void showProfile() {

    vector<string> navigation, compiledSideNav, compiledBanner, compiledContent;

    pair<string, string> credential = getCredentials(accountNumber);

    int totalLength = 0, adj; 

    size_t sideNav, maxSizeCredential, maxSizeHeight, spacingMenu;

    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    if(accountType == "Super Admin") {
        navigation = sideNavSuperAdmin;

        totalLength++;

    } else if (accountType == "Admin") {
        navigation = sideNavAdmin;

    } else if (accountType == "User") {
        navigation = sideNavUser;
    }

    sideNav = navigation.size();
    
    totalLength = banner[1].length() + 10; // Total size of content w/o sideNav

    maxSizeCredential = max((credential.first.length() + 10), (credential.second.length() + 10)); // Comparing length of username and password to center it

    maxSizeHeight = max(sideNav, banner.size()) + 11; // Comparing height of sideNav and (banner + accounts)
    
    spacingMenu = ((maxSizeHeight - 2) - sideNav); // Get total spacing for sideNav

    spacingMenu = (spacingMenu / 2) + (spacingMenu % 2); // Get half of spacing for sideNav

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

        int endSpacing = 0, startSpacing = 0;

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

        if (i == adj || i == maxSizeHeight - 3) { // Add divider between title and credentials, and between credentials and options
            temp += "┣";

            for (size_t j = 0; j < totalLength; j++) {
                temp += "━";
            }

            temp += "┫";

        } else if (i == adj + 4 || i == adj + 5) {
            int endSpacing = (totalLength - maxSizeCredential) / 2;
            int startSpacing = endSpacing + ((totalLength - maxSizeCredential) % 2);

            output << setw(startSpacing + 3) << left << "┃";

            if (i == adj + 4) {
                temp = "Username: " + credential.first;

            } else {
                temp = "Password: ";

                for (char& c : credential.second) {
                    temp += '*';
                }
            }

            output << temp;

            output << setw((totalLength - (startSpacing + temp.length())) + 3) << right  << "┃";
            temp = "";

        } else if (i < maxSizeHeight - 3) { // Add spacings
            output << setw(totalLength + 3) << left << "┃" << "┃";
            
        } else if (i == maxSizeHeight - 2) { // Add options
            string options = "";

            if (isOpen) {
                options = "[Esc] Close Menu        [U] Edit Username        [X] Edit Password";

            } else {
                options = "[M] Menu        [U] Edit Username        [X] Edit Password";
            }

            int endSpacing = (totalLength - options.length()) / 2;
            int startSpacing = endSpacing + (totalLength - options.length()) % 2;

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

        if (ch == 'm' && !isOpen) { // Open menu
            isOpen = true;
            showProfile();

        } else if (ch == 27 && isOpen) { // Close Menu
            isOpen = false;
            showProfile();

        } else if (ch == 'u') {
            isOpen = false;
            editUsername(accountNumber, "showProfile");

        } else if (ch == 'x') {

        } else {
            menus(ch);
        }
    }
}