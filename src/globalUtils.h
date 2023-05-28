#ifndef GLOBALUTILS_H
#define GLOBALUTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <sstream>
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

// Account related variables
extern vector<Account> developer;
extern vector<Account> admin;

// Product related variable
extern vector<Product> products;

// Vector navigationUtils related variables
extern vector<string> sideNavUser, sideNavAdmin, sideNavSuperAdmin, banner;
extern bool isOpen;

// Security related variables
extern string accountType;
extern int tries;

// Global related functions
void navigationUtils();
void globalMenu(char ch);

// Security related functions
void saveExpectedTime(time_t expectedTime);
time_t loadExpectedTime();
time_t calculateExpectedTime();
bool checkTimeMatches(time_t currentTime, time_t expectedTime);

// PIN code related functions
int devPinGenerator();
int getPinCode();
void changePinCode(int newPinCode);

void pinCodeLogin();
void pinCodeDisplay();


#endif