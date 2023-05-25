#include "headers.h"

using namespace std;

pair<string, string> getCredentials() {

    vector<Account> admins = readFromFile("accounts/admins.txt");
    vector<Account> users = readFromFile("accounts/users.txt");

    vector<Account> accounts;
    string username, password;

    // Compile both admin and user accounts into one
    accounts.insert(accounts.end(), superadmin.begin(), superadmin.end());
    accounts.insert(accounts.end(), admins.begin(), admins.end());
    accounts.insert(accounts.end(), users.begin(), users.end());

    for (auto& account : accounts) {
        if (accountNumber == account.accountNumber) {
            username = account.username;
            password = account.password;
        }
    }

    return make_pair(username, password);
}