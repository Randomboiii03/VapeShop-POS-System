#include "globalUtils.h"

using namespace std;

vector<Account> developer = {
    {"Developer", devPinGenerator()},
};

vector<Account> admin = {
    {"Admin", getPinCode()},
};

ExpectedTimeData timeData = loadExpectedTime();

string accountType = "Admin";
int tries = timeData.tries;

bool isOpen = false;

vector<string> sideNavUser, sideNavAdmin, sideNavSuperAdmin, banner;

int main()
{
    checkTime(timeData.expectedTime);

    navigationUtils();
    bannerUtils();

    // pinCodeLogin();

    return 0;
}