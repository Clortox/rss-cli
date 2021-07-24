///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// rss definition
//

#pragma once

#if _TESTS_ == 1
#include "config.hpp"
#endif

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <curl/curl.h>

namespace rss_utils {
    typedef std::vector<std::map<std::string, std::string>> item_map;
    class rss {
    public:
        rss();
        rss(const std::string&, bool = true);
        rss(const char*, bool = true);
        rss(const rss&);
        ~rss();
        rss& operator=(const rss&);
        rss* clone() const;

        bool isOk() const;

        void setURI(const std::string&, bool = true);
        void setURI(const char*, bool = true);
        std::string getURI() const;

        bool update();

        std::string getTitle()          const;
        std::string getLink()           const;
        std::string getDescription()    const;
        std::string getLanguage()       const;
        std::string getWebMaster()      const;
        std::string getCopyright()      const;
        std::string getPubDate()        const;
        std::string getManagingEditor() const;
        std::string getGenerator()      const;
        std::string getDocs()           const;
        std::string getTTL()            const;
        std::string getLastBuildDate()  const;

        //TODO
        //std::string getImage()          const;
        //std::string getCloud()          const;

        std::vector<std::map<std::string, std::string>> getItems() const;

    private:
        bool parse(const std::string&);

        bool ok;
        std::string uri;
        rapidxml::xml_node<> *item_node;
        rapidxml::xml_document<> doc;
    };

    size_t write_to_string(void*, size_t, size_t, std::string*);
}
