///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// rss output functions
//

#pragma once

#include <string>

#include "options.hpp"
#include "rss.hpp"

namespace rss_utils {
    std::string rss_to_list(const rss&, const option_flags*);
    std::string rss_to_items(const rss&, const option_flags*);
    bool rss_opts_empty(const option_flags*);

}
