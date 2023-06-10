#include "globalUtils.h"

using namespace std;

vector<Account> developer = {
    {"Developer", devPinGenerator()},
};

vector<Account> admin = {
    {"Admin", getPinCode()},
};

ExpectedTimeData timeData = loadExpectedTime();

string accountType = "User";
int tries = timeData.tries;

bool isOpen = false;

vector<string> navUser, navAdmin, navDeveloper, banner;

vector<string> categories = getCategories();
int nextCateg = 0;

int main()
{
    checkTime(timeData.expectedTime);

    navigationUtils();
    bannerUtils();

    Sleep(2000);

    productDisplay();

    return 0;
}