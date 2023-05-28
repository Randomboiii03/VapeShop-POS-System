#include "globalUtils.h"

using namespace std;

void navigationUtils()
{
    system("cls");
    SetConsoleOutputCP(CP_UTF8);

    // Insert sideNavUser
    sideNavUser.push_back("┃           ▀▀  █▄ ▄█ ██▀ █▄ █ █ █ ▀▀           ");
    sideNavUser.push_back("┃               █ ▀ █ █▄▄ █ ▀█ ▀▄█              ");
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃   █▀ █▀▄ ▀█  █▀▄ █▀▄ ▄▀▄ █▀▄ █ █ ▄▀▀ ▀█▀ ▄▀▀  ");
    sideNavUser.push_back("┃   █▄ █▀  ▄█  █▀  █▀▄ ▀▄▀ █▄▀ ▀▄█ ▀▄▄  █  ▄██  ");
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃           █▀ ▄▀▀ ▀█  ▄▀▀ ▄▀▄ █▀▄ ▀█▀          ");
    sideNavUser.push_back("┃           █▄ ▀▄▄ ▄█  ▀▄▄ █▀█ █▀▄  █           ");
    // sideNavUser.push_back("┃                                               ");
    // sideNavUser.push_back("┃                                               ");
    // sideNavUser.push_back("┃       █▀ █   ▀█  █   ▄▀▄ ▄▀  ▄▀▄ █ █ ▀█▀      ");
    // sideNavUser.push_back("┃       █▄ █▄▄ ▄█  █▄▄ ▀▄▀ ▀▄█ ▀▄▀ ▀▄█  █       ");

    // Insert sideNavAdmin
    sideNavAdmin.push_back("┃           ▀▀  █▄ ▄█ ██▀ █▄ █ █ █ ▀▀           ");
    sideNavAdmin.push_back("┃               █ ▀ █ █▄▄ █ ▀█ ▀▄█              ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃   █▀ █▀▄ ▀█  █▀▄ █▀▄ ▄▀▄ █▀▄ █ █ ▄▀▀ ▀█▀ ▄▀▀  ");
    sideNavAdmin.push_back("┃   █▄ █▀  ▄█  █▀  █▀▄ ▀▄▀ █▄▀ ▀▄█ ▀▄▄  █  ▄██  ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃         █▀ ▄▀▀ ▀█  ▄▀▀ ▄▀▄ █   ██▀ ▄▀▀        ");
    sideNavAdmin.push_back("┃         █▄ ▄██ ▄█  ▄██ █▀█ █▄▄ █▄▄ ▄██        ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃     █▀ █ ▀█   █▀▄ █ █▄ █   ▄▀▀ ▄▀▄ █▀▄ ██▀    ");
    sideNavAdmin.push_back("┃     █▄ █ ▄█   █▀  █ █ ▀█   ▀▄▄ ▀▄▀ █▄▀ █▄▄    ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃                                               ");
    sideNavAdmin.push_back("┃       █▀ █   ▀█  █   ▄▀▄ ▄▀  ▄▀▄ █ █ ▀█▀      ");
    sideNavAdmin.push_back("┃       █▄ █▄▄ ▄█  █▄▄ ▀▄▀ ▀▄█ ▀▄▀ ▀▄█  █       ");

    // Insert sideNavSuperAdmin
    sideNavSuperAdmin.push_back("┃           ▀▀  █▄ ▄█ ██▀ █▄ █ █ █ ▀▀           ");
    sideNavSuperAdmin.push_back("┃               █ ▀ █ █▄▄ █ ▀█ ▀▄█              ");
    sideNavSuperAdmin.push_back("┃                                               ");
    sideNavSuperAdmin.push_back("┃                                               ");
    sideNavSuperAdmin.push_back("┃                                               ");
    // sideNavSuperAdmin.push_back("┃     █▀ █ ▀█   █▀▄ █ █▄ █   ▄▀▀ ▄▀▄ █▀▄ ██▀    ");
    // sideNavSuperAdmin.push_back("┃     █▄ █ ▄█   █▀  █ █ ▀█   ▀▄▄ ▀▄▀ █▄▀ █▄▄    ");
    // sideNavSuperAdmin.push_back("┃                                               ");
    // sideNavSuperAdmin.push_back("┃                                               ");
    sideNavSuperAdmin.push_back("┃       █▀ █   ▀█  █   ▄▀▄ ▄▀  ▄▀▄ █ █ ▀█▀      ");
    sideNavSuperAdmin.push_back("┃       █▄ █▄▄ ▄█  █▄▄ ▀▄▀ ▀▄█ ▀▄▀ ▀▄█  █       ");
}

vector<string> navigationDisplay(vector<string> navigation, size_t maxSizeHeight, size_t sideNav, int paddingLeft)
{
    vector<string> compiledSideNav;

    for (size_t i = 0; i < maxSizeHeight; i++) // Compile newSideNav
    {
        if (i == 0) // Compile top outline
        {
            compiledSideNav.push_back("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        }
        else if (i - paddingLeft - 1 < sideNav) // Compile sideNav
        {
            compiledSideNav.push_back(navigation[i - paddingLeft - 1]);
        }
        else if (i == maxSizeHeight - 1) // Compile bottom outline
        {
            compiledSideNav.push_back("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        }
        else // Compile spacing for sideNav < content
        {
            compiledSideNav.push_back("┃                                               ");
        }
    }

    return compiledSideNav;
}