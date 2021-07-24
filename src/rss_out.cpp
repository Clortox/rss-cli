///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// rss output functions implementation
//

#include "rss_out.hpp"

using namespace rss_utils;

std::string rss_utils::rss_to_list(const rss& rss_obj, const option_flags* flags){
    std::string ret;

    if(flags->title){
        ret += rss_obj.getTitle() + "\n";
    }
    if(flags->link){
        ret += rss_obj.getLink() + "\n";
    }
    if(flags->description){
        ret += rss_obj.getDescription() + "\n";
    }
    if(flags->language){
        ret += rss_obj.getLanguage() + "\n";
    }
    if(flags->webmaster){
        ret += rss_obj.getWebMaster() + "\n";
    }
    if(flags->copyright){
        ret += rss_obj.getCopyright() + "\n";
    }
    if(flags->pubdate){
        ret += rss_obj.getPubDate() + "\n";
    }
    if(flags->managingeditor){
        ret += rss_obj.getManagingEditor() + "\n";
    }
    if(flags->generator){
        ret += rss_obj.getGenerator() + "\n";
    }
    if(flags->docs){
        ret += rss_obj.getDocs() + "\n";
    }
    if(flags->ttl){
        ret += rss_obj.getTTL() + "\n";
    }
    if(flags->builddate){
        ret += rss_obj.getLastBuildDate() + "\n";
    }

    if(ret.length() > 0)
        ret.pop_back();
    else if (ret.length() == 0)
        ret = "<No arguments given>";

    return ret;
}
