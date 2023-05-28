#include "headers.h"

using namespace std;

vector<Account> developer = {
    {"Developer", generateDeveloperPin()},
};

vector<Account> admin = {
    {"Admin", getPinCode()},
};

string accountType = "User";
bool isOpen = false;

int tries = 0;

vector<string> sideNavUser;
vector<string> sideNavAdmin;
vector<string> sideNavSuperAdmin;
vector<string> banner;

int main()
{

    navigations();
    login();

    return 0;
}