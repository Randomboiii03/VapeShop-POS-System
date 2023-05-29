#include "globalUtils.h"

using namespace std;

void bannerUtils()
{
    // Insert banner
    banner.push_back("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    banner.push_back("                                                                                           ");
    banner.push_back(" ▄▄▄· ▌ ▐·▐▄• ▄    ▄▄▄·▄▄▄         ▐▄▄▄▄▄▄ . ▄▄· ▄▄▄▄▄   ▌ ▐· ▄▄▄·  ▄▄▄·      ▄▄▄    ▐▄• ▄ ");
    banner.push_back("▐█ ▄█▪█·█▌ █▌█▌▪  ▐█ ▄█▀▄ █· ▄█▀▄  ▪·██▀▄.▀·▐█ ▌▪•██    ▪█·█▌▐█ ▀█ ▐█ ▄█ ▄█▀▄ ▀▄ █·   █▌█▌▪");
    banner.push_back(" ██▀·▐█▐█• ·██·    ██▀·▐▀▀▄ ▐█▌.▐▌▪▄ ██▐▀▀▪▄██ ▄▄ ▐█.▪  ▐█▐█•▄█▀▀█  ██▀·▐█▌.▐▌▐▀▀▄    ·██· ");
    banner.push_back("▐█▪·• ███ ▪▐█·█▌  ▐█▪·•▐█•█▌▐█▌.▐▌▐▌▐█▌▐█▄▄▌▐███▌ ▐█▌·   ███ ▐█▪ ▐▌▐█▪·•▐█▌.▐▌▐█•█▌  ▪▐█·█▌");
    banner.push_back(".▀   . ▀  •▀▀ ▀▀  .▀   .▀  ▀ ▀█▄▀▪ ▀▀▀• ▀▀▀ ·▀▀▀  ▀▀▀   . ▀   ▀  ▀ .▀    ▀█▄▀▪.▀  ▀  •▀▀ ▀▀");
    banner.push_back("                                                                                           ");
    banner.push_back("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

string bannerDisplay(int count, int bannerSize, int totalLength, string title)
{
    string temp = "";
    ostringstream output;

    Padding padding;

    if (count <= banner.size())
    {
        if (count == banner.size()) // Get new bannerSize for title
        {
            bannerSize = title.length();
        }

        padding = centerPadding(totalLength, bannerSize, 2); // Get left and right padding

        if (count == 0) // Add corner outline when menu !isOpen
        {
            if (isOpen)
            {
                temp += "┳";
            }
            else
            {
                temp += "┏";
            }
        }
        else if (count == banner.size() - 1) // Add custom vertical divider
        {
            temp += "┣";
        }

        if (count == 0 || count == banner.size() - 1) // Add additional horizontal outline before and after of banner
        {
            temp += addSpacingWithOutline(padding.paddingLeft) + banner[count] + addSpacingWithOutline(padding.paddingRight);

            if (count == 0)
            {
                temp += "┓";
            }
            else
            {
                temp += "┫";
            }
        }
        else // Add spacing before and after of banner < totalLength of accounts, and title
        {
            output << setw(padding.paddingLeft + 3) << left << "┃";

            if (count == banner.size())
            {
                output << title;
            }
            else
            {
                output << banner[count];
            }

            output << setw(padding.paddingRight + 3) << right << "┃";
        }
    }

    if (temp == "") // Compile non-outline
    {
        temp = output.str();
        output = ostringstream();
    }

    return temp;
}