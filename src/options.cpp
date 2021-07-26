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
    std::cout << " [-u, --uri] URI        URI of the rss stream\n";
    std::cout << "                        Also accepts '-' to take input\n";
    std::cout << "                        from stdin (stops once a newline is reached)\n\n";

    std::cout << "Channel information:\n";
    std::cout << " [-t, --title]          Get title of channel\n";
    std::cout << " [-l, --link]           Get link to channel\n";
    std::cout << " [-d, --description]    Get description of channel\n";
    std::cout << " [-L, --language]       Get language code of channel\n";
    std::cout << " [-m, --webmaster]      Get webMaster's email\n";
    std::cout << " [-c, --copyright]      Get copyright\n";
    std::cout << " [-p, --pubdate]        Get publishing date\n";
    std::cout << " [-e, --managingeditor] Get managing editor\n";
    std::cout << " [-g, --generator]      Get generator of this feed\n";
    std::cout << " [-o, --docs]           Get link to RSS documentation\n";
    std::cout << " [-w, --ttl]            Get ttl, time that channel can be\n";
    std::cout << "                        cached before being updated\n";
    std::cout << " [-b, --builddate]      Get last time the channel's\n";
    std::cout << "                        content changed\n";
    std::cout << " [-Q, --imageurl]       Get channel image URL\n";
    std::cout << " [-I, --imagetitle]     Get image title, same as ALT in html\n";
    std::cout << " [-E, --imagelink]      Get link to site, image will act as a link\n";
    std::cout << " [-W, --imagewidth]     Get width of image\n";
    std::cout << " [-H, --imageheight]    Get height of image\n";
    std::cout << " [-D, --clouddomain]    Get domain of feed update service\n";
    std::cout << " [-P, --cloudport]      Get port of feed update service\n";
    std::cout << " [-A, --cloudpath]      Get path to access for feed update service\n";
    std::cout << " [-R, --cloudregister]  Get register procedure for feed update service\n";
    std::cout << " [-O, --cloudprotocol]  Get protocol feed update service uses\n";
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
    std::cout << " [-C, --category]       Get category list\n";
    std::cout << " [-f, --comments]       Get link to comments\n";
    std::cout << " [-G, --guid]           Get GUID\n";
    std::cout << " [-p, --pubdate]        Get publishing date\n";
    std::cout << " [-s, --source]         Get source of item\n";
    std::cout << " [-U, --enclosureurl]   Get enclosure URL\n";
    std::cout << " [-T, --enclosuretype]  Get enclosure MIME type\n";
    std::cout << " [-K, --enclosurelength]Get enclosure length, in bytes\n\n";

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
            case 'L':
                if(current_item == nullptr)
                    ret->language ^= 1;
                else
                    std::cerr << "-L option not understood in context of --item; ignoring" << std::endl;
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
            case 'e':
                if(current_item == nullptr)
                    ret->managingeditor ^= 1;
                else
                    std::cerr << "-e option not understood in context of --item; ignoring" << std::endl;
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
            case 'Q':
                if(current_item == nullptr)
                    ret->imageurl ^= 1;
                else
                    std::cerr << "-Q option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'I':
                if(current_item == nullptr)
                    ret->imagetitle ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'E':
                if(current_item == nullptr)
                    ret->imagelink ^= 1;
                else 
                    std::cerr << "-E option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'W':
                if(current_item == nullptr)
                    ret->imagewidth ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'H':
                if(current_item == nullptr)
                    ret->imageheight ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'D':
                if(current_item == nullptr)
                    ret->clouddomain ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'P':
                if(current_item == nullptr)
                    ret->cloudport ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'A':
                if(current_item == nullptr)
                    ret->cloudpath ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'R':
                if(current_item == nullptr)
                    ret->cloudregister ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
                break;
            case 'O':
                if(current_item == nullptr)
                    ret->cloudprotocol ^= 1;
                else
                    std::cerr << "-I option not understood in context of --item; ignoring" << std::endl;
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
            case 'C':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-C --category]" << std::endl;
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
            case 'G':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-G --guid]" << std::endl;
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
            case 'U':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-U --enclosureurl]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->enclosureurl ^= 1;
                break;
            case 'T':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-T --enclosuretype]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else 
                    current_item->enclosuretype ^= 1;
                break;
            case 'K':
                if(current_item == nullptr){
                    std::cerr << "Invalid option in this context: [-K --enclosurelength]" << std::endl;
                    std::cerr << "Did you provide the [-i --index] flag first?" << std::endl;
                } else
                    current_item->enclosurelength ^= 1;
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

