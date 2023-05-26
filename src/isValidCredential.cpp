#include "headers.h"

using namespace std;

bool validateUsername(const string& username) {
    // Regular expression pattern for username validation
    regex pattern("^[a-zA-Z0-9_-]{6,16}$");
    
    return regex_match(username, pattern);
}

bool isUsernameAvailable(const string& username) {
    // Read txt file everytime function called/loaded
    vector<Account> admins = readFromFile("accounts/admins.txt");
    vector<Account> users = readFromFile("accounts/users.txt");

    vector<Account> accounts;

    // Compile both admin and user accounts into one vector
    accounts.insert(accounts.end(), superadmin.begin(), superadmin.end());
    accounts.insert(accounts.end(), admins.begin(), admins.end());
    accounts.insert(accounts.end(), users.begin(), users.end());

    for (auto& account : accounts) {
        if (username == account.username) {
            return false;
        }
    }

    return true;
}

bool validatePassword(const string& password) {
    // Regular expression pattern for password validation
    regex pattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[_!@#$%^&*]).{8,}$");
    
    return regex_match(password, pattern);
}