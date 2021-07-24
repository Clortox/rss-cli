///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// entry point
//

#include <iostream>
#include <getopt.h>
#include "config.hpp"
#include "rss.hpp"

#if _TESTS_ == 1
#include "tests.hpp"
#endif

struct option_flags {
    unsigned int title : 1;
    unsigned int link : 1;
    unsigned int description : 1;
    unsigned int language : 1;
    unsigned int webmaster : 1;
    unsigned int copyright : 1;
    unsigned int pubdate : 1;
    unsigned int managingeditor : 1;
    unsigned int generator : 1;
    unsigned int docs : 1;
    unsigned int ttl : 1;
    unsigned int builddate : 1;

    std::string uri;
};

//cli options
static struct option long_options[] =
{
    {"uri",   required_argument,    0, 'u'},
    {"title", no_argument,          0, 't'},
    {"link",  no_argument,          0, 'l'},
    {"description", no_argument,    0, 'd'},
    {"language", no_argument,       0, 'e'},
    {"webmaster", no_argument,      0, 'm'},
    {"copyright", no_argument,      0, 'c'},
    {"pubdate", no_argument,        0, 'p'},
    {"managingeditor", no_argument, 0, 'q'},
    {"generator", no_argument,      0, 'g'},
    {"docs", no_argument,           0, 'o'},
    {"ttl", no_argument,            0, 'w'},
    {"builddate", no_argument,      0, 'b'},
    {"help", no_argument,           0, 'h'},
    {0, 0, 0, 0},
};

constexpr char* optarg_string = "u:tldemcpqgowbh";

void help(char* progName){
    std::cout << "Usage: " << progName << "[-u FEED_URI]\n";
    std::cout << "Options:\n";
    std::cout << "Required Options:\n";
    std::cout << " [-u, --uri]            URI of the rss stream\n\n";

    std::cout << "Channel information:\n";
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
    std::cout << "                        cached before being updated\n";
    std::cout << " [-b, --builddate]      Get last time the channel's\n";
    std::cout << "                        content changed\n\n";

    std::cout << "General options:\n";
    std::cout << " [-h, --help]           Show this message\n";

    exit(1);
}

option_flags* parse_options(int argc, char** argv) {
    int option_index = 0;
    int c;
    option_flags* ret = new option_flags;

    while(true){
        c = getopt_long(argc, argv, optarg_string, 
                long_options, &option_index);
        if(c == -1)
            break;

        switch(c){
            case 'u':
                ret->uri = std::string(optarg);
                break;
            case 't':
                ret->title ^= 1;
                break;
            case 'l':
                ret->link ^= 1;
                break;
            case 'd':
                ret->description ^= 1;
                break;
            case 'e':
                ret->language ^= 1;
                break;
            case 'm':
                ret->webmaster ^= 1;
                break;
            case 'c':
                ret->copyright ^= 1;
                break;
            case 'p':
                ret->pubdate ^= 1;
                break;
            case 'q':
                ret->managingeditor ^= 1;
                break;
            case 'g':
                ret->generator ^= 1;
                break;
            case 'o':
                ret->docs ^= 1;
                break;
            case 'w':
                ret->ttl ^= 1;
                break;
            case 'b':
                ret->builddate ^= 1;
                break;
            case '?':
                std::cerr << "Misunderstood flag!" << std::endl;
            case 'h':
                help(argv[0]);
                break;
            default:
                abort();
        }
    }
    
    if(ret->uri == ""){
        std::cerr << "Missing required option! -u/--uri" << std::endl;
        exit(-1);
    }


    return ret;
}


int main(int argc, char** argv) {
#if _TESTS_ == 1
    rss_utils::testRSS();
    return 0;
#endif

    //get the passed options
    option_flags* opts = parse_options(argc, argv);

    //setup the rss object

    





    return 0;
}
