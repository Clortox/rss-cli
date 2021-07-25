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
constexpr char optarg_string[] = ":u:tldemcpqgowbi::azfjsh";

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

    {"item", optional_argument,     0, 'i'},
    {"author", no_argument,         0, 'a'},
    {"category", no_argument,       0, 'z'},
    {"comments", no_argument,       0, 'f'},
    {"guid", no_argument,           0, 'j'},
    {"source", no_argument,         0, 's'},

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

    item_flags* items;
    unsigned int item_count;
    std::string uri;
};


void help(char*);
option_flags* parse_options(int, char**);
