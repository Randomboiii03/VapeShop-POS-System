#include "globalUtils.h"

using namespace std;

// Return string for outline
string addSpacingWithOutline(int totalLength)
{
    string temp = "";

    for (size_t j = 0; j < totalLength; j++) // Outline
    {
        temp += "━";
    }

    return temp;
}

// Return string for spacing
string addSpacingWithoutOutline(int times, int totalLength)
{
    ostringstream output;
    string temp;

    for (size_t i = 0; i < times; i++) // Spaces
    {
        output << setw(totalLength) << left << "";

        if (times > 1) {
            output << endl;
        }
    }

    temp = output.str();

    return temp;
}

string addNRepeat(string text, int length)
{
    string temp = "";
    
    for (int i = 0; i < length; i++)
    {
        temp += text;
    }

    return temp;
}

// Calculate padding
Padding centerPadding(int maxWidth, int textLength, int divisor)
{
    Padding padding;
    padding.paddingRight = (maxWidth - textLength) / divisor;
    padding.paddingLeft = padding.paddingRight + ((maxWidth - textLength) % divisor);

    return padding;
}

void centerText(string text, int textLength)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int maxWidth = csbi.dwMaximumWindowSize.X;

    SHORT centerX = (maxWidth - textLength) / 2;
    SHORT centerY = csbi.dwCursorPosition.Y;
    
    COORD pos = {centerX, centerY};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    cout << text << endl;
}

void setInputPos(string text, int textLength, SHORT y, int padding, string label)
{
    string temp;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int maxWidth = csbi.dwMaximumWindowSize.X;

    SHORT centerX = ((maxWidth - textLength) / 2) + padding + label.length() + 1;
    SHORT centerY = y;

    COORD pos = {centerX, centerY};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}