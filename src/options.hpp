///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// options parsing
//

#pragma once

#include <string>
#include <iostream>
#include <getopt.h>

//cli options
constexpr char optarg_string[] = ":u:i::tldLmcpegowbQIEWCHDPAROacfGsUTK";

static struct option long_options[] =
{
    {"uri",   required_argument,    0, 'u'},

    {"title", no_argument,          0, 't'},
    {"link",  no_argument,          0, 'l'},
    {"description", no_argument,    0, 'd'},
    {"language", no_argument,       0, 'L'},
    {"webmaster", no_argument,      0, 'm'},
    {"copyright", no_argument,      0, 'c'},
    {"pubdate", no_argument,        0, 'p'},
    {"managingeditor", no_argument, 0, 'e'},
    {"generator", no_argument,      0, 'g'},
    {"docs", no_argument,           0, 'o'},
    {"ttl", no_argument,            0, 'w'},
    {"builddate", no_argument,      0, 'b'},

    {"imageurl", no_argument,       0, 'Q'},
    {"imagetitle", no_argument,     0, 'I'},
    {"imagelink", no_argument,      0, 'E'},
    {"imagewidth", no_argument,     0, 'W'},
    {"imageheight", no_argument,    0, 'H'},

    {"clouddomain", no_argument,    0, 'D'},
    {"cloudport", no_argument,      0, 'P'},
    {"cloudpath", no_argument,      0, 'A'},
    {"cloudregister", no_argument,  0, 'R'},
    {"cloudprotocl", no_argument,   0, 'O'},

    {"item", optional_argument,     0, 'i'},
    {"author", no_argument,         0, 'a'},
    {"category", no_argument,       0, 'C'},
    {"comments", no_argument,       0, 'f'},
    {"guid", no_argument,           0, 'G'},
    {"source", no_argument,         0, 's'},

    {"enclosureurl", no_argument,   0, 'U'},
    {"enclosuretype", no_argument,  0, 'T'},
    {"enclosurelength", no_argument,0, 'K'},

    {"help", no_argument,           0, 'h'},
    {0, 0, 0, 0},
};

struct item_flags {
    unsigned int title : 1;
    unsigned int link : 1;
    unsigned int description : 1;
    unsigned int author : 1;
    unsigned int category : 1;
    unsigned int comments : 1;
    unsigned int guid : 1;
    unsigned int pubdate : 1;
    unsigned int source : 1;

    unsigned int enclosureurl : 1;
    unsigned int enclosuretype : 1;
    unsigned int enclosurelength : 1;

    int index;
};

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

    unsigned int imageurl : 1;
    unsigned int imagetitle : 1;
    unsigned int imagelink : 1;
    unsigned int imagewidth : 1;
    unsigned int imageheight : 1;

    unsigned int clouddomain : 1;
    unsigned int cloudport : 1;
    unsigned int cloudpath : 1;
    unsigned int cloudregister : 1;
    unsigned int cloudprotocol : 1;

    item_flags* items;
    unsigned int item_count;
    std::string uri;
};


void help(char*);
option_flags* parse_options(int, char**);
