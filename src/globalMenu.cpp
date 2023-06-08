#include "globalUtils.h"

using namespace std;

void globalMenu(char ch)
{
    if (ch == 'l' && isOpen) // Logout
    {
        isOpen = false;
        accountType = "User";

        string temp = "Logging out...";
        centerText(temp, temp.length());

        Sleep(2000);
        productDisplay();
    }
    else if (ch == 'p' && isOpen && accountType != "Developer") // Product
    {
        isOpen = false;
        productDisplay();
    }
    else if (ch == 'c' && isOpen && accountType == "User") // Cart
    {
        isOpen = false;
        cartDisplay();
    }
    else if (ch == 's' && isOpen && accountType == "Admin") // Sales
    {
        isOpen = false;
    }
    else if (ch == 'i' && isOpen && accountType != "User") // Pincode
    { 
        isOpen = false;
        pinCodeDisplay();
    }
}