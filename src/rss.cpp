///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// rss implementation
//

#include "rss.hpp"

using namespace rss_utils;

rss::rss() {
    _uri = "";
    _ok = false;
    _item_node = nullptr;
}

rss::rss(const std::string& rss_uri, bool perf_update){
    _uri = rss_uri;
    _item_node = nullptr;
    _ok = false;
    if(perf_update)
        update();
}

rss::rss(const char* rss_uri, bool perf_update){
    _uri = std::string(rss_uri);
    _ok = false;
    _item_node = nullptr;
    if(perf_update)
        update();
}

rss::rss(const rss& rhs){
    _uri = rhs._uri;
    _ok = false;
    _item_node = nullptr;
    update();
}

rss::~rss(){
    _doc.clear();
}

rss& rss::operator=(const rss& rhs){
    if(this != &rhs){
        _uri = rhs._uri;
        _ok = false;
        _item_node = nullptr;
        update();
    }
    return *this;
}

rss* rss::clone() const {
    rss* clone = new rss(*this);
    return clone;
}

bool rss::isOk() const { return _ok; }

void rss::setURI(const std::string& rss_uri, bool perf_update) {
    _uri = rss_uri;
    _ok = false;
    if(perf_update)
        update();
}

void rss::setURI(const char* rss_uri, bool perf_update) {
    _uri = std::string(rss_uri);
    _ok = false;
    if(perf_update)
        update();
}

std::string rss::getURI() const { return _uri; }

bool rss::update() {
    std::string result;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, _uri.c_str());
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
    _ok = false;
    return false;
}

std::string rss::getTitle() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("title");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getLink() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("link");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getDescription() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("description");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getLanguage() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("language");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getWebMaster() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("webMaster");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getCopyright() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("copyright");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getPubDate() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("pubDate");
    if(tmp == 0)
        return "";
    return tmp->value();

}

std::string rss::getManagingEditor() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("managingEditor");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getGenerator() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("generator");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getDocs() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("docs");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string rss::getTTL() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("ttl");
    if(tmp == 0)
        return "";
    return tmp->value();

}

std::string rss::getLastBuildDate() const {
    if(!_ok)
        return "";

    rapidxml::xml_node<> *tmp = _item_node->first_node("lastBuildDate");
    if(tmp == 0)
        return "";
    return tmp->value();
}

int rss::getItemCount() const {
    if(!_ok)
        return -1;

    return _items.size();
}

std::vector<item> rss::getItems() {
    if(!_ok)
        return std::vector<item>();

    if(!_items.empty())
        return _items;

    //items is empty, have not processed the items yet
    std::vector<rapidxml::xml_node<>*> items;
    items = parseItems();
    for(auto it = items.begin(); it != items.end(); ++it){
        item i(*it);
        _items.push_back(i);
    }

    return _items;
}

item& rss::getItem(const int index) {
    getItems();
    return _items[index];
}

const item& rss::getItem(const int index) const {
    return _items[index];
}

item& rss::operator[](const int index) {
    return getItem(index);
}

const item& rss::operator[](const int index) const {
    return getItem(index);
}

std::vector<rapidxml::xml_node<>*> rss::parseItems() {
    std::vector<rapidxml::xml_node<>*> items;

    if(!_ok)
        return items;

    rapidxml::xml_node<> *first_item = _item_node->first_node("item");
    //there are no items, return empty vector
    if(first_item == 0)
        return items;

    for(; first_item != NULL; first_item = first_item->next_sibling())
        items.push_back(first_item);

    /*
    for(; first_item != NULL; first_item = first_item->next_sibling()){
        std::map<std::string, std::string> tmp_item;
        for(rapidxml::xml_node<> *item_val = first_item->first_node();
                item_val != NULL; item_val = item_val->next_sibling())
            tmp_item[item_val->name()] = item_val->value();
        items.push_back(tmp_item);
    }
    */

    return items;
}

bool rss::parse(const std::string& rss_str){
    _ok = true;

    //parse, check for errors in xml doc
    try {
        _doc.parse<0>(_doc.allocate_string(rss_str.c_str()));
    } catch (const std::runtime_error& e){
        std::cerr << "rss::parse() runtime error: " << e.what() << std::endl;
        _ok = false;
    } catch (const rapidxml::parse_error& e){
        std::cerr << "rss::parse() error with file: " << e.what() << std::endl;
        _ok = false;
    }

    //verify that it is an rss file
    rapidxml::xml_node<> *tmp = _doc.first_node("rss");
    if(tmp == NULL){
        std::cerr << "rss::parse() error with file: XML is not an rss feed!" << std::endl;
        _ok = false;
    } else {
        tmp = tmp->first_node("channel");
        if(tmp == NULL){
            std::cerr << "rss::parse() error with file: RSS feed has no channels!" 
                << std::endl;
            _ok = false;
        }
    }

    if(_ok){
        _item_node = tmp;
    }
    return _ok;
}

size_t rss_utils::write_to_string(void* ptr, size_t size, size_t nmemb, std::string* s){
    s->append(static_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

item::item() {}
item::item(rapidxml::xml_node<>* node){
    _item = node;
}

item::item(const item& rhs){
    _item = rhs._item;
}

item::~item() {}

item& item::operator=(const item& rhs){
    if(this != &rhs){
        _item = rhs._item;
    }
    return *this;
}

item* item::clone() const {
    item* clone = new item(*this);
    return clone;
}

std::string item::getTitle() const {
    rapidxml::xml_node<>* tmp = _item->first_node("title");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getLink() const {
    rapidxml::xml_node<>* tmp = _item->first_node("link");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getDescription() const {
    rapidxml::xml_node<>* tmp = _item->first_node("description");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getAuthor() const {
    rapidxml::xml_node<>* tmp = _item->first_node("author");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getCategory() const {
    rapidxml::xml_node<>* tmp = _item->first_node("category");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getComments() const {
    rapidxml::xml_node<>* tmp = _item->first_node("comments");
    if(tmp == 0)
        return "";
    return tmp->value();
}

/*
std::string item::getEnclosure() const {
    rapidxml::xml_node<>* tmp = _item->first_node("enclosure");
    if(tmp == 0)
        return "";
    return tmp->value();
}
*/

std::string item::getGuid() const {
    rapidxml::xml_node<>* tmp = _item->first_node("guid");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getPubDate() const {
    rapidxml::xml_node<>* tmp = _item->first_node("pubDate");
    if(tmp == 0)
        return "";
    return tmp->value();
}

std::string item::getSource() const {
    rapidxml::xml_node<>* tmp = _item->first_node("source");
    if(tmp == 0)
        return "";
    return tmp->value();
}

