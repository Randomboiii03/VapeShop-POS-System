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
        output << setw(totalLength + 3) << left << "";

        if (times > 1) {
            output << endl;
        }
    }

    temp = output.str();

    return temp;
}

// Calculate padding
Padding centerPadding(int totalLength, int otherLength, int divisor)
{
    Padding padding;
    padding.paddingRight = (totalLength - otherLength) / divisor;
    padding.paddingLeft = padding.paddingRight + ((totalLength - otherLength) % divisor);

    return padding;
}