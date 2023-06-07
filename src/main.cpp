#include "globalUtils.h"

using namespace std;

vector<Account> developer = {
    {"Developer", devPinGenerator()},
};

vector<Account> admin = {
    {"Admin", getPinCode()},
};

vector<Cart> cart = {
    {10002, 100},
    {10005, 400},
    {10046, 50},
    {10008, 200},
    {10100, 700}
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