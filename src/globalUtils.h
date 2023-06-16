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
#include <algorithm>
#include <filesystem>
#include <conio.h>
#include <locale>
#include <cctype>

using namespace std;

struct Account
{
    string accountType;
    string pinCode;
};

struct Product
{
    int productID;
    string category;
    string brandName;
    string productName;
    string productDesc;
    float price;
    int stock;
    bool isAvailable;
};

struct Cart
{
    int productID;
    int quantity;
};

struct Sales
{
    int productID;
    float price;
    int quantity;
    string paymentMode;
    string transactionNum;
    string currentTime;
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

// Product related variables
extern vector<string> categories;
extern int nextCateg;

// Sales related variables
extern int saleFilterIndex;

// Vector navigationUtils related variables
extern vector<string> navUser, navAdmin, navDeveloper, banner;
extern bool isOpen;

// Security related variables
extern string accountType;
extern int tries;

// Global related functions
void navigationUtils();
vector<string> navigationDisplay(vector<string> navigation, int maxHeight);

void bannerUtils();
vector<string> bannerDisplay(int maxWidth, int bannerWidth, string title);

string olTLCorner();
string olTRCorner();
string olBRCorner();
string olBLCorner();
string olVLine();
string olHLine();
string olLVDivider();
string olRVDivider();
string olTHDivider();
string olBHDivider();
string olILDivider();

void globalMenu(char ch);

string addNRepeat(string text, int length);
Padding centerPadding(int maxWidth, int textLength, int divisor);

void centerText(string text, int textLength);
void setInputPos(string text, int textLength, SHORT y, int padding, string label);

string priceFormat(float value);
vector<string> splitString(string text, char delimiter);
string toLowercase(const string &str);

// Security related functions
void saveExpectedTime(time_t expectedTime);
ExpectedTimeData loadExpectedTime();
time_t calculateExpectedTime();
bool checkTime(time_t expectedTime);

// PIN code related functions
string devPinGenerator();
string getPinCode();
void changePinCode(string newPinCode);
void pinCodeEditor();

void pinCodeLogin();
void pinCodeDisplay();

// Product related functions
void productDisplay();
void productView(int prodIndex, vector<Product> products);
void productSearch(string search);
void productAdd();

void saveProducts(const vector<Product> &products);
vector<Product> loadProductsByCategory(const string &category);
vector<Product> loadAllProducts();
void deleteProduct(int prodIndex, vector<Product> products);
vector<Product> searchProductsByName(const string &substring);

bool containsCategory(const vector<string> &categories, const string &category);
vector<string> getCategories();
int getMaxLengthProduct(const vector<Product> &data, int columnIndex, string columnName);
string checkCategory(string categ);

// Cart related functions
void cartDisplay();

void saveCart(const vector<Cart> &data);
vector<Cart> loadCart();
void deleteProductInCart(int cartIndex);
void editQuantityInCart(int cartIndex, int maxHeight);

bool checkStock(int cartIndex, int quantity);
void inCart(int prodIndex, int quantity);
void emptyCart();
int getMaxLengthCart(const vector<Cart> &data, const vector<Product> &data2, int columnIndex, string headerName);

// Checkout related functions
void checkoutDisplay(string paymentMode);

void addSales(const vector<Sales> &data);

string getCurrentDateTime();

// Sales related functions
void salesDisplay(time_t currentDate);
void salesView(int saleIndex, time_t currentDate);

void saveSales(const vector<Sales> &data);
vector<Sales> loadSales(time_t currentDate);
vector<Sales> loadAllSales();
vector<Sales> loadByDaySales(time_t currentDate);
vector<Sales> loadByWeekSales(time_t currentDate);
vector<Sales> loadByMonthSales(time_t currentDate);
vector<Sales> loadByYearSales(time_t currentDate);
void deleteSales(int saleIndex, time_t currentDate);

string getSalesTitle(time_t currentDate);
int getMaxLengthSales(const vector<Sales> &data, const vector<Product> &data2, int columnIndex, string headerName);
vector<string> getWeekDates(time_t currentDate);

#endif