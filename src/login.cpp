#include "headers.h"

using namespace std;

string username, password;
bool isValid;

void login() {
    
    system("cls");

    vector<Account> accounts;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    accounts.insert(accounts.end(), superadmin.begin(), superadmin.end());
    accounts.insert(accounts.end(), admins.begin(), admins.end());
    accounts.insert(accounts.end(), users.begin(), users.end());

    for (auto& account : accounts) {
        if (username == account.username && password == account.password) {
            
            if (!account.isActive) {
                cout << "Account is disabled" << endl;
                Sleep(1000);
                login();
                break;

            } else {
                isValid = true;
                accountNumber = account.accountNumber;

                cout << account.accountType << " successfully login!" << endl;
                Sleep(1000);
                break;
            }
        }
    }

    if (!isValid) {
        cout << "Wrong username or password!" << endl;
        Sleep(1000);

        login();
    }
}