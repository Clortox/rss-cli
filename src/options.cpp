///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-23-21
// options implementation
//

#include "options.hpp"

void help(char* progName){
    std::cout << "Usage: " << progName << " [-u FEED_URI] [CHANNEL FLAGS] ";
    std::cout << "[-i ITEM_INDEX] [ITEM FLAGS]\n";
    std::cout << "Options:\n";
    std::cout << "Required Options:\n";
    std::cout << " [-u, --uri] URI        URI of the rss stream\n\n";

    std::cout << "Channel information:\n";
    std::cout << " [-t, --title]          Get title of channel\n";
    std::cout << " [-l, --link]           Get link to channel\n";
    std::cout << " [-d, --description]    Get description of channel\n";
    std::cout << " [-e, --language]       Get language code of channel\n";
    std::cout << " [-m, --webmaster]      Get webMaster's email\n";
    std::cout << " [-c, --copyright]      Get copyright\n";
    std::cout << " [-p, --pubdate]        Get publishing date\n";
    std::cout << " [-q, --managingeditor] Get managing editor\n";
    std::cout << " [-g, --generator]      Get generator of this feed\n";
    std::cout << " [-o, --docs]           Get link to RSS documentation\n";
    std::cout << " [-w, --ttl]            Get ttl, time that channel can be\n";
    std::cout << "                        cached before being updated\n";
    std::cout << " [-b, --builddate]      Get last time the channel's\n";
    std::cout << "                        content changed\n";
    std::cout << " [-i, --item] INDEX     Provide index of item to display\n";
    std::cout << "                        If no index is provided, assume the first\n";
    std::cout << "                        item in the feed. All following flags will\n";
    std::cout << "                        be parsed as item options, till another\n";
    std::cout << "                        item is provided\n\n";

    std::cout << "Item options:\n";
    std::cout << " [-t, --title]          Get title of item\n";
    std::cout << " [-l, --link]           Get link\n";
    std::cout << " [-d, --description]    Get description\n";
    std::cout << " [-a, --author]         Get author\n";
    std::cout << " [-z, --category]       Get category list\n";
    std::cout << " [-f, --comments]       Get link to comments\n";
    std::cout << " [-j, --guid]           Get GUID\n";
    std::cout << " [-p, --pubdate]        Get publishing date\n";
    std::cout << " [-s, --source]         Get source of item\n\n";

    std::cout << "General options:\n";
    std::cout << " [-h, --help]           Show this message\n\n";

    std::cout << "For more information, refer to the RSS 2.0 documentation\n";
    std::cout << "https://validator.w3.org/feed/docs/rss2.html\n";

    exit(1);
}

option_flags* parse_options(int argc, char** argv) {
    int option_index = 0;
    int c;

    item_flags* current_item = nullptr;
    option_flags* ret = new option_flags;

    ret->item_count = 0;
    ret->items = nullptr;

    while(true){
        c = getopt_long(argc, argv, optarg_string, 
                long_options, &option_index);
        if(c == -1)
            break;

        switch(c){
            case 'u':
                ret->uri = std::string(optarg);
                break;
            case 't':
                if(current_item == nullptr)
                    ret->title ^= 1;
                else
                    current_item->title ^= 1;
                break;
            case 'l':
                if(current_item == nullptr)
                    ret->link ^= 1;
                else
                    current_item->link ^= 1;
                break;
            case 'd':
                if(current_item == nullptr)
                    ret->description ^= 1;
                else
                    current_item->description ^= 1;
                break;
            case 'e':
                if(current_item == nullptr)
                    ret->language ^= 1;
                else
                    std::cerr << "-e option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'm':
                if(current_item == nullptr)
                    ret->webmaster ^= 1;
                else
                    std::cerr << "-m option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'c':
                if(current_item == nullptr)
                    ret->copyright ^= 1;
                else
                    std::cerr << "-c option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'p':
                if(current_item == nullptr)
                    ret->pubdate ^= 1;
                else
                    current_item->pubdate ^= 1;
                break;
            case 'q':
                if(current_item == nullptr)
                    ret->managingeditor ^= 1;
                else
                    std::cerr << "-q option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'g':
                if(current_item == nullptr)
                    ret->generator ^= 1;
                else
                    std::cerr << "-g option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'o':
                if(current_item == nullptr)
                    ret->docs ^= 1;
                else
                    std::cerr << "-o option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'w':
                if(current_item == nullptr)
                    ret->ttl ^= 1;
                else
                    std::cerr << "-w option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'b':
                if(current_item == nullptr)
                    ret->builddate ^= 1;
                else
                    std::cerr << "-b option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'i':
                if(ret->items == nullptr){
                    ret->items = new item_flags[ret->item_count + 1];
                    current_item = &(ret->items[0]);
                    ret->item_count++;
                    current_item->index = optarg ? atoi(optarg) : 0;
                } else {
                    item_flags* new_flags = new item_flags[ret->item_count + 1];
                    for(unsigned int i=0;i<ret->item_count;++i)
                        new_flags[i] = ret->items[i];
                    delete ret->items;
                    ret->items = new_flags;
                    current_item = &(ret->items[ret->item_count]);
                    ret->item_count++;
                    current_item->index = optarg ? atoi(optarg) : 0;
                }
                break;
            case 'a':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-a --author]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->author ^= 1;
                break;
            case 'z':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-z --category]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->category ^= 1;
                break;
            case 'f':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-f --comments]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->comments ^= 1;
                break;
            case 'j':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-j --guid]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->guid ^= 1;
                break;
            case 's':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-s --source]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->source ^= 1;
                break;
            case ':': //go here if flag that requires argument is passed, but no arg given
                switch(optopt){
                    case 'i':
                        if(ret->items == nullptr){
                            ret->item_count++;
                            ret->items = new item_flags[ret->item_count];
                            current_item = &(ret->items[0]);
                            current_item->index = 1;
                        } else {
                            item_flags* new_flags = new item_flags[ret->item_count + 1];
                            for(unsigned int i=0;i<ret->item_count;++i)
                                new_flags[i] = ret->items[i];
                            delete ret->items;
                            ret->items = new_flags;
                            current_item = &(ret->items[ret->item_count]);
                            ret->item_count++;
                            current_item->index = 1;
                        }
                        break;
                    default:
                        std::cerr << "Invalid use: option -" << (char)optopt 
                            << " requires an argument" << std::endl;
                        break;
                }
                break;
            case '?':
                std::cerr << "Unknown option: " << (char)optopt << std::endl;
            case 'h':
                help(argv[0]);
                break;
            default:
                abort();
        }
    }

    if(ret->uri == ""){
        std::cerr << "Missing required option! -u/--uri" << std::endl;
        exit(-1);
    }
    return ret;
}

