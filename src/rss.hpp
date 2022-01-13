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
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include <curl/curl.h>

namespace rss_utils {
    typedef std::vector<std::map<std::string, std::string>> item_map;
    class item;
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

        std::string getTitle()                  const;
        std::string getLink()                   const;
        std::string getDescription()            const;
        std::string getLanguage()               const;
        std::string getWebMaster()              const;
        std::string getCopyright()              const;
        std::string getPubDate()                const;
        std::string getManagingEditor()         const;
        std::string getGenerator()              const;
        std::string getDocs()                   const;
        std::string getTTL()                    const;
        std::string getLastBuildDate()          const;

        std::string getImageURL()               const;
        std::string getImageTitle()             const;
        std::string getImageLink()              const;
        int         getImageWidth()             const;
        int         getImageHeight()            const;

        std::string getCloudDomain()            const;
        int         getCloudPort()              const;
        std::string getCloudPath()              const;
        std::string getCloudRegisterProcedure() const;
        std::string getCloudProtocol()          const;

        int         getItemCount()         const;
        std::vector<item> getItems();

        item& getItem(const int);
        const item& getItem(const int) const;
        item& operator[](const int);
        const item& operator[](const int) const;


    private:
        bool parse(const std::string&);
        std::vector<rapidxml::xml_node<>*> parseItems();
        std::string cdata_to_string(const rapidxml::xml_node<>*) const;

        bool _ok;
        std::string _uri;
        rapidxml::xml_node<> *_item_node;
        rapidxml::xml_document<> _doc;
        std::vector<item> _items;
    };

    class item {
    public:
        item();
        item(rapidxml::xml_node<>*);
        item(const item&);
        ~item();
        item& operator=(const item&);
        item* clone() const;

        std::string getTitle()           const;
        std::string getLink()            const;
        std::string getDescription()     const;
        std::string getAuthor()          const;
        std::string getCategory()        const;
        std::string getComments()        const;
        std::string getGuid()            const;
        bool        getGuidPermaLink()   const;
        std::string getPubDate()         const;
        std::string getSource()          const;
        
        std::string getEnclosureURL()    const;
        std::string getEnclosureType()   const;
        int         getEnclosureLength() const;


    private:
        std::string cdata_to_string(const rapidxml::xml_node<>*) const;

        rapidxml::xml_node<> *_item;
    };

    size_t write_to_string(void*, size_t, size_t, std::string*);
}
