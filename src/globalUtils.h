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
    string pinCode;
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

struct Padding
{
    int paddingLeft;
    int paddingRight;
};

struct ExpectedTimeData
{
    time_t expectedTime;
    int tries;
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
vector<string> navigationDisplay(vector<string> navigation, size_t maxSizeHeight, size_t sideNav, int paddingLeft);
void bannerUtils();
string bannerDisplay(int count, int bannerSize, int totalLength, string title);
void globalMenu(char ch);
string addSpacingWithOutline(int totalLength);
string addSpacingWithoutOutline(int times, int totalLength);
Padding centerPadding(int totalLength, int otherLength, int divisor);

// Security related functions
void saveExpectedTime(time_t expectedTime);
ExpectedTimeData loadExpectedTime();
time_t calculateExpectedTime();
void checkTime(time_t expectedTime);

// PIN code related functions
string devPinGenerator();
string getPinCode();
void changePinCode(string newPinCode);
void pinCodeEditor();

void pinCodeLogin();
void pinCodeDisplay();

#endif