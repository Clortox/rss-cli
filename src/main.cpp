///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// entry point
//

#include <iostream>
#include <string>
#include <getopt.h>

#include "config.hpp"
#include "rss_out.hpp"
#include "options.hpp"
#include "rss.hpp"

#if _TESTS_ == 1
#include "tests.hpp"
#endif

int main(int argc, char** argv) {
#if _TESTS_ == 1
    rss_utils::testRSS();
    rss_utils::testItems();
    return 0;
#endif

    //get the passed options
    option_flags* opts = parse_options(argc, argv);

    //setup the rss object
    rss_utils::rss feed(opts->uri);
    if(!feed.isOk())
        exit(-1);


    //display requested attributes and items
    std::string output = "";
    if(!rss_utils::rss_opts_empty(opts))
        output = rss_utils::rss_to_list(feed, opts);

    if(opts->items != nullptr){
        feed.getItems();
        output += "\n" + rss_utils::rss_to_items(feed, opts);
    }

    std::cout << "Item count: " << feed.getItemCount() << std::endl;

    std::cout << output << std::endl;

    delete opts;
    return 0;
}
