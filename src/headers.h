#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <fstream>
// #include <utility>
// #include <cmath>
#include <sstream>
// #include <regex>
// #include <limits>
#include <stdexcept>
#include <ctime>
#include <bitset>
#include <chrono>

using namespace std;

struct Account
{
    string accountType;
    int pinCode;
};

struct Product
{
    int productNumber;
    string category;
    string productName;
    string productDesc;
    double price;
    bool isAvailable;
};

extern vector<Account> developer;
extern vector<Account> admin;

extern vector<Product> products;

extern vector<string> sideNavUser;
extern vector<string> sideNavAdmin;
extern vector<string> sideNavSuperAdmin;
extern vector<string> banner;

extern string accountType;
extern int tries;
// extern int accountNumber;

extern bool isOpen;

void login();
void navigations();
// void showAccounts();
void menus(char ch);
// int getMaxLengthAcc(const vector<Account>& data, int additionalDividerWidth, size_t columnIndex);
// void writeToFile(const string& filename, const vector<Account>& accounts);
// vector<Account> readFromFile(const string& filename);
// void showProfile();
// pair<string, string> getCredentials(int accNumber);
// string getAccountType (int accNumber);
// void editUsername(int accNumber, string function);
// void editPassword(int accNumber, string function);
// bool validateUsername(const string& username);
// bool validatePassword(const string& password);
// bool isUsernameAvailable(const string& username);
int generateDeveloperPin();
int getPinCode();

#endif