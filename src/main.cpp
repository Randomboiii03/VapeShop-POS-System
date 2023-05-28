#include "globalUtils.h"

using namespace std;

vector<Account> developer = {
    {"Developer", devPinGenerator()},
};

vector<Account> admin = {
    {"Admin", getPinCode()},
};

string accountType = "Admin";
int tries = 0;

bool isOpen = false;

vector<string> sideNavUser, sideNavAdmin, sideNavSuperAdmin, banner;

int main()
{
    navigationUtils();
    bannerUtils();

    pinCodeLogin();

    return 0;
}