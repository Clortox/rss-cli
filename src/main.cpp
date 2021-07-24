///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// entry point
//

#include <iostream>
#include "config.hpp"
#include "rss.hpp"

#if _TESTS_ == 1
#include "tests.hpp"
#endif

void help(char* progName){
    std::cout << "Usage: " << progName << "[-u FEED_URI]\n";
    std::cout << "Options:\n";
    std::cout << " [-u, --uri]            URI of the rss stream\n\n";
    std::cout << " [-t, --title]          Get title of channel\n";
    std::cout << " [-l, --link]           Get link to channel\n";
    std::cout << " [-d, --description]    Get Description of channel\n";
    std::cout << " [-e, --language]       Get language code of channel\n";
    std::cout << " [-m, --webmaster]      Get webMaster's email\n";
    std::cout << " [-c, --copyright]      Get copyright\n";
    std::cout << " [-p, --pubdate]        Get publishing date\n";
    std::cout << " [-q, --managingeditor] Get Managing Editor\n";
    std::cout << " [-g, --generator]      Get generator of this feed\n";
    std::cout << " [-o, --docs]           Get link to RSS documentation\n";
    std::cout << " [-w, --ttl]            Get ttl, time that channel can be\n";
    std::cout << "                         cached before being updated\n";
    std::cout << " [-b, --builddate]      Get last time the channel's\n";
    std::cout << "                         content changed\n";

}

int main(int argc, char** argv) {
#if _TESTS_ == 1
    rss_utils::testRSS();
    return 0;
#endif






}
