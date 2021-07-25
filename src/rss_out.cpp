///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// rss output functions implementation
//

#include "rss_out.hpp"

using namespace rss_utils;

std::string rss_utils::rss_to_list(const rss& rss_obj, const option_flags* flags){
    std::string ret;

    if(flags->title)
        ret += rss_obj.getTitle() + "\n";
    if(flags->link)
        ret += rss_obj.getLink() + "\n";
    if(flags->description)
        ret += rss_obj.getDescription() + "\n";
    if(flags->language)
        ret += rss_obj.getLanguage() + "\n";
    if(flags->webmaster)
        ret += rss_obj.getWebMaster() + "\n";
    if(flags->copyright)
        ret += rss_obj.getCopyright() + "\n";
    if(flags->pubdate)
        ret += rss_obj.getPubDate() + "\n";
    if(flags->managingeditor)
        ret += rss_obj.getManagingEditor() + "\n";
    if(flags->generator)
        ret += rss_obj.getGenerator() + "\n";
    if(flags->docs)
        ret += rss_obj.getDocs() + "\n";
    if(flags->ttl)
        ret += rss_obj.getTTL() + "\n";
    if(flags->builddate)
        ret += rss_obj.getLastBuildDate() + "\n";

    if(ret.length() > 0)
        ret.pop_back();
    else if (ret.length() == 0)
        ret = "<No arguments given>";

    return ret;
}

std::string rss_utils::rss_to_items(const rss& rss_obj, const option_flags* flags){
    item_flags* items = flags->items;
    int maxItem = rss_obj.getItemCount();
    std::string ret;

    for(unsigned int i=0; i < flags->item_count; ++i, ++items){
        //if has a valid index
        if(items->index >= 0 && items->index < maxItem){
            rss_utils::item cur_item = rss_obj[items->index];
            if(items->title)
                ret += cur_item.getTitle() + "\n";
            if(items->link)
                ret += cur_item.getLink() + "\n";
            if(items->description)
                ret += cur_item.getDescription() + "\n";
            if(items->author)
                ret += cur_item.getAuthor() + "\n";
            if(items->category)
                ret += cur_item.getCategory() + "\n";
            if(items->comments)
                ret += cur_item.getComments() + "\n";
            if(items->guid)
                ret += cur_item.getGuid() + "\n";
            if(items->pubdate)
                ret += cur_item.getPubDate() + "\n";
            if(items->source)
                ret += cur_item.getSource() + "\n";
        } else
            std::cerr << "Index on item " << i << " is not valid!" << std::endl;
    }

    if(ret.length() > 0)
        ret.pop_back();
    else
        ret = "<No arguments given for items>";

    return ret;
}
