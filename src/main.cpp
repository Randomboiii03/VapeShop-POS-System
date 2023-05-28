#include "globalUtils.h"

using namespace std;

vector<Account> developer = {
    {"Developer", devPinGenerator()},
};

vector<Account> admin = {
    {"Admin", getPinCode()},
};

string accountType = "User";
bool isOpen = false;

int tries = 0;

vector<string> sideNavUser, sideNavAdmin, sideNavSuperAdmin, banner;

int main()
{

    navigationUtils();
    pinCodeLogin();

    return 0;
}