#include "headers.h"

using namespace std;

int getMaxLengthAcc(const vector<Account>& data, int additionalDividerWidth, size_t columnIndex) {

    int max_length = 0;

    // Check for the datas width
    for (const auto& account : data) {
        switch (columnIndex) {
            case 0:
                max_length = max(max_length, static_cast<int>(to_string(account.accountNumber).length()));
                break;
            case 1:
                max_length = max(max_length, static_cast<int>(account.accountType.length()));
                break;
            case 2:
                max_length = max(max_length, static_cast<int>(account.username.length()));
                break;
            case 3:
                max_length = max(max_length, static_cast<int>(account.password.length()));
                break;
            case 4:
                max_length = max(max_length, static_cast<int>((account.isActive ? string("Active") : string("Banned/Disabled")).length()) );
                break;
            default:
                // Invalid column index
                break;
        }
    }

    // Check for the header width
    switch (columnIndex) {
        case 0:
            max_length = max(max_length, static_cast<int>(string("Account Number").length()));
            break;
        case 1:
            max_length = max(max_length, static_cast<int>(string("Account Type").length()));
            break;
        case 2:
            max_length = max(max_length, static_cast<int>(string("Username").length()));
            break;
        case 3:
            max_length = max(max_length, static_cast<int>(string("Password").length()));
            break;
        case 4:
            max_length = max(max_length, static_cast<int>(string("Status").length()));
            break;
        default:
            // Invalid column index
            break;
    }

    return max_length + additionalDividerWidth;
}