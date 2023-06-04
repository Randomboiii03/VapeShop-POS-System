#include "globalUtils.h"

using namespace std;

void navigationUtils()
{
    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Insert navUser
    navUser.push_back("           ▀▀  █▄ ▄█ ██▀ █▄ █ █ █ ▀▀           ");
    navUser.push_back("               █ ▀ █ █▄▄ █ ▀█ ▀▄█              ");
    navUser.push_back("                                               ");
    navUser.push_back("                                               ");
    navUser.push_back("                                               ");
    navUser.push_back("   █▀ █▀▄ ▀█  █▀▄ █▀▄ ▄▀▄ █▀▄ █ █ ▄▀▀ ▀█▀ ▄▀▀  ");
    navUser.push_back("   █▄ █▀  ▄█  █▀  █▀▄ ▀▄▀ █▄▀ ▀▄█ ▀▄▄  █  ▄██  ");
    navUser.push_back("                                               ");
    navUser.push_back("                                               ");
    navUser.push_back("           █▀ ▄▀▀ ▀█  ▄▀▀ ▄▀▄ █▀▄ ▀█▀          ");
    navUser.push_back("           █▄ ▀▄▄ ▄█  ▀▄▄ █▀█ █▀▄  █           ");

    // Insert navAdmin
    navAdmin.push_back("           ▀▀  █▄ ▄█ ██▀ █▄ █ █ █ ▀▀           ");
    navAdmin.push_back("               █ ▀ █ █▄▄ █ ▀█ ▀▄█              ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("   █▀ █▀▄ ▀█  █▀▄ █▀▄ ▄▀▄ █▀▄ █ █ ▄▀▀ ▀█▀ ▄▀▀  ");
    navAdmin.push_back("   █▄ █▀  ▄█  █▀  █▀▄ ▀▄▀ █▄▀ ▀▄█ ▀▄▄  █  ▄██  ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("         █▀ ▄▀▀ ▀█  ▄▀▀ ▄▀▄ █   ██▀ ▄▀▀        ");
    navAdmin.push_back("         █▄ ▄██ ▄█  ▄██ █▀█ █▄▄ █▄▄ ▄██        ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("     █▀ █ ▀█   █▀▄ █ █▄ █   ▄▀▀ ▄▀▄ █▀▄ ██▀    ");
    navAdmin.push_back("     █▄ █ ▄█   █▀  █ █ ▀█   ▀▄▄ ▀▄▀ █▄▀ █▄▄    ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("                                               ");
    navAdmin.push_back("       █▀ █   ▀█  █   ▄▀▄ ▄▀  ▄▀▄ █ █ ▀█▀      ");
    navAdmin.push_back("       █▄ █▄▄ ▄█  █▄▄ ▀▄▀ ▀▄█ ▀▄▀ ▀▄█  █       ");

    // Insert navDeveloper
    navDeveloper.push_back("           ▀▀  █▄ ▄█ ██▀ █▄ █ █ █ ▀▀           ");
    navDeveloper.push_back("               █ ▀ █ █▄▄ █ ▀█ ▀▄█              ");
    navDeveloper.push_back("                                               ");
    navDeveloper.push_back("                                               ");
    navDeveloper.push_back("                                               ");
    navDeveloper.push_back("       █▀ █   ▀█  █   ▄▀▄ ▄▀  ▄▀▄ █ █ ▀█▀      ");
    navDeveloper.push_back("       █▄ █▄▄ ▄█  █▄▄ ▀▄▀ ▀▄█ ▀▄▀ ▀▄█  █       ");
}

vector<string> navigationDisplay(vector<string> navigation, int maxHeight)
{
    vector<string> newNavigation;
    Padding padding = centerPadding(maxHeight, navigation.size(), 2);

    for (size_t i = 0; i < maxHeight; i++)
    {
        if (i == 0) // Top outline display
        {
            newNavigation.push_back(olTLCorner() + addNRepeat(olHLine(), navigation[2].length()));
        }
        else if (i == maxHeight - 1) // Bottom outline display
        {
            newNavigation.push_back(olBLCorner() + addNRepeat(olHLine(), navigation[2].length()));
        }
        else if (i - padding.paddingLeft - 1 < navigation.size()) // Navigation display
        {
            newNavigation.push_back(olVLine() + navigation[i - padding.paddingLeft - 1]);
        }
        else // Spacer display
        {
            newNavigation.push_back(olVLine() + addNRepeat(" ", navigation[2].length()));
        }
    }

    return newNavigation;
}