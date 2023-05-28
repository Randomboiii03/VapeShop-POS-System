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
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃                                               ");
    sideNavUser.push_back("┃       █▀ █   ▀█  █   ▄▀▄ ▄▀  ▄▀▄ █ █ ▀█▀      ");
    sideNavUser.push_back("┃       █▄ █▄▄ ▄█  █▄▄ ▀▄▀ ▀▄█ ▀▄▀ ▀▄█  █       ");

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

    // Insert banner
    banner.push_back("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    banner.push_back("                                                                                           ");
    banner.push_back(" ▄▄▄· ▌ ▐·▐▄• ▄    ▄▄▄·▄▄▄         ▐▄▄▄▄▄▄ . ▄▄· ▄▄▄▄▄   ▌ ▐· ▄▄▄·  ▄▄▄·      ▄▄▄    ▐▄• ▄ ");
    banner.push_back("▐█ ▄█▪█·█▌ █▌█▌▪  ▐█ ▄█▀▄ █· ▄█▀▄  ▪·██▀▄.▀·▐█ ▌▪•██    ▪█·█▌▐█ ▀█ ▐█ ▄█ ▄█▀▄ ▀▄ █·   █▌█▌▪");
    banner.push_back(" ██▀·▐█▐█• ·██·    ██▀·▐▀▀▄ ▐█▌.▐▌▪▄ ██▐▀▀▪▄██ ▄▄ ▐█.▪  ▐█▐█•▄█▀▀█  ██▀·▐█▌.▐▌▐▀▀▄    ·██· ");
    banner.push_back("▐█▪·• ███ ▪▐█·█▌  ▐█▪·•▐█•█▌▐█▌.▐▌▐▌▐█▌▐█▄▄▌▐███▌ ▐█▌·   ███ ▐█▪ ▐▌▐█▪·•▐█▌.▐▌▐█•█▌  ▪▐█·█▌");
    banner.push_back(".▀   . ▀  •▀▀ ▀▀  .▀   .▀  ▀ ▀█▄▀▪ ▀▀▀• ▀▀▀ ·▀▀▀  ▀▀▀   . ▀   ▀  ▀ .▀    ▀█▄▀▪.▀  ▀  •▀▀ ▀▀");
    banner.push_back("                                                                                           ");
    banner.push_back("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}