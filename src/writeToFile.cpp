#include "headers.h"

using namespace std;

void writeToFile(const string& filename, const vector<Account>& accounts) {

    ofstream file(filename);

    // Insert account into txt file
    for (const auto& account : accounts) {
        file << account.accountNumber << " " << account.accountType << " " << account.username << " " << account.password << " " << account.isActive << endl;
    }
    
    file.close();
}