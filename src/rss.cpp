///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// rss implementation
//

#include "rss.hpp"

using namespace rss_utils;

rss::rss() {
    uri = "";
    ok = false;
    item_node = nullptr;
}

rss::rss(const std::string& rss_uri, bool perf_update){
    uri = rss_uri;
    item_node = nullptr;
    ok = false;
    if(perf_update)
        update();
}

rss::rss(const char* rss_uri, bool perf_update){
    uri = std::string(rss_uri);
    ok = false;
    item_node = nullptr;
    if(perf_update)
        update();
}

rss::rss(const rss& rhs){
    uri = rhs.uri;
    ok = false;
    item_node = nullptr;
    update();
}

rss::~rss(){
    doc.clear();
}

rss& rss::operator=(const rss& rhs){
    if(this != &rhs){
        uri = rhs.uri;
        ok = false;
        item_node = nullptr;
        update();
    }
    return *this;
}

rss* rss::clone() const {
    rss* clone = new rss(*this);
    return clone;
}

bool rss::isOk() const { return ok; }

void rss::setURI(const std::string& rss_uri, bool perf_update) {
    uri = rss_uri;
    ok = false;
    if(perf_update)
        update();
}

void rss::setURI(const char* rss_uri, bool perf_update) {
    uri = std::string(rss_uri);
    ok = false;
    if(perf_update)
        update();
}

std::string rss::getURI() const { return uri; }

bool rss::update() {
    std::string result;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, rss_utils::write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res == CURLE_OK){
            return parse(result);
        } else {
            std::cerr << "curl_easy_perform(curl) failed: "
                << curl_easy_strerror(res) << std::endl;
        }
    }
    ok = false;
    return false;
}

std::string rss::getTitle() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("title");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getLink() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("link");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getDescription() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("description");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getLanguage() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("language");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getWebMaster() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("webMaster");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getCopyright() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("copyright");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getPubDate() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("pubDate");
    if(tmp == 0)
        return "";
    return tmp->value();

}

std::string rss::getManagingEditor() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("managingEditor");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getGenerator() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("generator");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getDocs() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("docs");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getTTL() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("ttl");
    if(tmp == 0)
        return "";
    return tmp->value();

}

std::string rss::getLastBuildDate() const {
    if(!ok)
        return "";

    rapidxml::xml_node<> *tmp = item_node->first_node("lastBuildDate");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::vector<std::map<std::string, std::string>> rss::getItems() const {
    std::vector<std::map<std::string, std::string>> items;

    if(!ok)
        return items;

    rapidxml::xml_node<> *first_item = item_node->first_node("item");
    //there are no items, return empty vector
    if(first_item == 0)
        return items;

    for(; first_item != NULL; first_item = first_item->next_sibling()){
        std::map<std::string, std::string> tmp_item;
        for(rapidxml::xml_node<> *item_val = first_item->first_node();
                item_val != NULL; item_val = item_val->next_sibling())
            tmp_item[item_val->name()] = item_val->value();
        items.push_back(tmp_item);
    }

    return items;
}

bool rss::parse(const std::string& rss_str){
    ok = true;

    //parse, check for errors in xml doc
    try {
        doc.parse<0>(doc.allocate_string(rss_str.c_str()));
    } catch (const std::runtime_error& e){
        std::cerr << "rss::parse() runtime error: " << e.what() << std::endl;
        ok = false;
    } catch (const rapidxml::parse_error& e){
        std::cerr << "rss::parse() error with file: " << e.what() << std::endl;
        ok = false;
    }

    //verify that it is an rss file
    rapidxml::xml_node<> *tmp = doc.first_node("rss");
    if(tmp == NULL){
        std::cerr << "rss::parse() error with file: XML is not an rss feed!" << std::endl;
        ok = false;
    } else {
        tmp = tmp->first_node("channel");
        if(tmp == NULL){
            std::cerr << "rss::parse() error with file: RSS feed has no channels!" 
                << std::endl;
            ok = false;
        }
    }

    if(ok){
        item_node = tmp;
    }
    return ok;
}

size_t rss_utils::write_to_string(void* ptr, size_t size, size_t nmemb, std::string* s){
    s->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}
