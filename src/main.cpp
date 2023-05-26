#include "headers.h"

using namespace std;

vector<Account> superadmin = {
    {0, "Super Admin", "super_admin", "super69", true},
};


string accountType = "";
int accountNumber;

bool isOpen = false;

vector<string> sideNavUser;
vector<string> sideNavAdmin;
vector<string> sideNavSuperAdmin;
vector<string> banner;

int main() {

    navigations();
    login();

    return 0;
}