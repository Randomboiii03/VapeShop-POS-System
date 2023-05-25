#include "headers.h"

using namespace std;

vector<Account> readFromFile(const string& filename) {
    vector<Account> accounts;

    ifstream file(filename);

    if (file.is_open()) {
        while (!file.eof()) {
            Account account;

            file >> account.accountNumber >> account.accountType >> account.username >> account.password >> account.isActive;

            if (!file.eof()) {
                accounts.push_back(account); // Insert account in vector
            }
        }

        file.close();
    }
    
    return accounts;
}