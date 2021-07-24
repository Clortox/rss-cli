///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// entry point
//

#include <iostream>
#include <string>
#include <getopt.h>

#include "config.hpp"
#include "options.hpp"
#include "rss.hpp"

#if _TESTS_ == 1
#include "tests.hpp"
#endif

int main(int argc, char** argv) {
#if _TESTS_ == 1
    rss_utils::testRSS();
    return 0;
#endif

    //get the passed options
    option_flags* opts = parse_options(argc, argv);

    //setup the rss object
    rss_utils::rss feed(opts->uri);
    if(!feed.isOk())
        exit(-1);

    //display requested attributes


    





    return 0;
}
