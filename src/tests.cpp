///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// tests implementation
//

#include "tests.hpp"

using namespace rss_utils;

void rss_utils::testRSS() {
    std::cout << "===== test RSS class =====" << std::endl;
    std::string url1 = "https://www.feedforall.com/sample-feed.xml";
    std::string bad_url = "https://www.not_a_real_link.com/";

    //test default constructor
    {
        rss_utils::rss feed;
        assert(feed.getURI() == "");
        assert(feed.isOk() == false);
        std::cout << "def cont tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed(url1);
        assert(feed.getURI() == url1);
        assert(feed.isOk() == true);
        std::cout << "std::string& cont tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed(url1.c_str());
        assert(feed.getURI() == url1);
        assert(feed.isOk() == true);
        std::cout << "char* cont tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed(url1);
        rss_utils::rss feed2(feed);
        assert(feed2.getURI() == url1);
        assert(feed2.isOk() == true);
        std::cout << "copy cont tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed(url1);
        rss_utils::rss feed2 = feed;
        assert(feed2.getURI() == url1);
        assert(feed2.isOk() == true);
        std::cout << "assignment operator tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed(url1);
        rss_utils::rss* feed2 = feed.clone();
        assert(feed2->getURI() == url1);
        assert(feed2->isOk() == true);
        std::cout << "clone functions tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed(url1);
        feed.setURI(bad_url);
        assert(feed.getURI() == bad_url);
        assert(feed.isOk() == false);
        std::cout << "std::string& setURI tests passed!" << std::endl;
    }
    {
        rss_utils::rss feed;
        feed.setURI(bad_url.c_str());
        assert(feed.getURI() == bad_url);
        assert(feed.isOk() == false);
        std::cout << "char* setURI tests passed!" << std::endl;
    }
    /*
    {
        rss_utils::rss feed(url1);
        rss_utils::item_map items = feed.getItems();
        for(auto it = items.begin(); it != items.end(); ++it){
            std::cout << "=== Item ===" << std::endl;
            std::cout << "Item: " << (*it)["title"] << std::endl;
            std::cout << "Description: " << (*it)["description"] << std::endl;
            std::cout << "Link: " << (*it)["link"] << std::endl;
            std::cout << "pubDate: " << (*it)["pubDate"] << std::endl;
        }
        std::cout << "=== Done with Items ===" << std::endl;
    }
    */
    std::cout << "===== test RSS class =====" << std::endl;
}

void rss_utils::testItems() {
    std::cout << "===== test RSS Items =====" << std::endl;    
    std::string url1 = "https://www.feedforall.com/sample-feed.xml";
    std::string bad_url = "https://www.not_a_real_link.com/";

    {
        rss_utils::rss feed(url1);
        std::vector<rss_utils::item> items = feed.getItems();
        //display items
        std::cout << "===== Item =====" << std::endl;
        for(auto it = items.begin(); it != items.end(); ++it){
            std::cout << (*it).getTitle() << std::endl;
            std::cout << (*it).getLink() << std::endl;
            std::cout << (*it).getDescription() << std::endl;
            std::cout << (*it).getAuthor() << std::endl;
            std::cout << (*it).getCategory() << std::endl;
            std::cout << (*it).getComments() << std::endl;
            std::cout << (*it).getGuid() << std::endl;
            std::cout << (*it).getPubDate() << std::endl;
            std::cout << (*it).getSource() << std::endl;
            std::cout << "===== Item =====" << std::endl;
        }
    }

    std::cout << "===== test RSS Items =====" << std::endl;

}
