#include "headers.h"

using namespace std;

void menus(char ch)
{
    if (ch == 'l' && isOpen) // Logout
    {
        isOpen = false;
        accountType = "";
        int pinCode = 0;
    }
    else if (ch == 'p' && isOpen && accountType != "Developer") // Product
    {
        isOpen = false;
    }
    else if (ch == 'c' && isOpen && accountType == "User") // Cart
    {
        isOpen = false;
    }
    else if (ch == 's' && isOpen && accountType == "Admin") // Sales
    {
        isOpen = false;
    }
    else if (ch == 'i' && isOpen && accountType != "User") // Pincode
    { 
        isOpen = false;
    }
}