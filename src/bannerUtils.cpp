#include "globalUtils.h"

using namespace std;

void bannerUtils()
{
    // Insert banner
    banner.push_back("                                                                                           ");
    banner.push_back("                                                                                           ");
    banner.push_back(" ▄▄▄· ▌ ▐·▐▄• ▄    ▄▄▄·▄▄▄         ▐▄▄▄▄▄▄ . ▄▄· ▄▄▄▄▄   ▌ ▐· ▄▄▄·  ▄▄▄·      ▄▄▄    ▐▄• ▄ ");
    banner.push_back("▐█ ▄█▪█·█▌ █▌█▌▪  ▐█ ▄█▀▄ █· ▄█▀▄  ▪·██▀▄.▀·▐█ ▌▪•██    ▪█·█▌▐█ ▀█ ▐█ ▄█ ▄█▀▄ ▀▄ █·   █▌█▌▪");
    banner.push_back(" ██▀·▐█▐█• ·██·    ██▀·▐▀▀▄ ▐█▌.▐▌▪▄ ██▐▀▀▪▄██ ▄▄ ▐█.▪  ▐█▐█•▄█▀▀█  ██▀·▐█▌.▐▌▐▀▀▄    ·██· ");
    banner.push_back("▐█▪·• ███ ▪▐█·█▌  ▐█▪·•▐█•█▌▐█▌.▐▌▐▌▐█▌▐█▄▄▌▐███▌ ▐█▌·   ███ ▐█▪ ▐▌▐█▪·•▐█▌.▐▌▐█•█▌  ▪▐█·█▌");
    banner.push_back(".▀   . ▀  •▀▀ ▀▀  .▀   .▀  ▀ ▀█▄▀▪ ▀▀▀• ▀▀▀ ·▀▀▀  ▀▀▀   . ▀   ▀  ▀ .▀    ▀█▄▀▪.▀  ▀  •▀▀ ▀▀");
    banner.push_back("                                                                                           ");
    banner.push_back("");
}

vector<string> bannerDisplay(int maxWidth, int bannerWidth, string title)
{
    vector<string> newBanner;
    string temp;

    Padding padding;

    for (int i = 0; i <= banner.size() + 1; i++)
    {
        if (i == 0) // Top outline display
        {
            if (isOpen)
            {
                temp = olTHDivider();
            }
            else
            {
                temp = olTLCorner();
            }

            temp += addNRepeat(olHLine(), maxWidth) + olTRCorner();
        }
        else if (i == banner.size() - 1 || i == banner.size() + 1) // Bottom outline display
        {
            if (isOpen)
            {
                temp = olLVDivider();
            }
            else
            {
                temp = olLVDivider();
            }

            temp += addNRepeat(olHLine(), maxWidth) + olRVDivider();
        }
        else if (i == banner.size()) // Title display
        {
            padding = centerPadding(maxWidth, title.length(), 2);
            temp = olVLine() + addNRepeat(" ", padding.paddingLeft) + title + addNRepeat(" ", padding.paddingRight) + olVLine();
        }
        else // Banner display
        {
            padding = centerPadding(maxWidth, (bannerWidth - 10), 2);
            temp = olVLine() + addNRepeat(" ", padding.paddingLeft) + banner[i] + addNRepeat(" ", padding.paddingRight) + olVLine();
        }

        newBanner.push_back(temp);
    }

    return newBanner;
}