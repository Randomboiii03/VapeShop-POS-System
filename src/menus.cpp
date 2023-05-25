#include "headers.h"

using namespace std;

void menus(char ch) {

    if (ch == 'l' && isOpen) { // Logout
        isOpen = false;
        accountType = "";
        accountNumber = -1;

    } else if (ch == 'p' && isOpen) { // Profile
        isOpen = false;
        showProfile();

    } else if (ch == 'a' && isOpen && accountType != "User") { // Accounts
        isOpen = false;
        showAccounts();

    } else if (ch == 's' && isOpen && accountType != "Super Admin") { // Services
        isOpen = false; 
        

    } else if (ch == 'b' && isOpen && accountType == "User") { // Booking List
        isOpen = false;
        

    } else if (ch == 'e' && isOpen && accountType == "Admin") { //Sales
        isOpen = false;

    }
}