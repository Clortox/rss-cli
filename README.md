rss-cli
=======

A unix-inspired cli application for interacting with rss feeds

Build
=====

Depends on
----------

- rapidxml
- libcurl

To build
---------

`make all`

To install
-----------

`make install`

Usage
=====

`./bin/rss-cli --help`

Full help message

```
Usage: ./bin/rss-cli [-u FEED_URI] [CHANNEL FLAGS] [-i ITEM_INDEX] [ITEM FLAGS]
Options:
Required Options:
 [-u, --uri] URI        URI of the rss stream

Channel information:
 [-t, --title]          Get title of channel
 [-l, --link]           Get link to channel
 [-d, --description]    Get description of channel
 [-L, --language]       Get language code of channel
 [-m, --webmaster]      Get webMaster's email
 [-c, --copyright]      Get copyright
 [-p, --pubdate]        Get publishing date
 [-e, --managingeditor] Get managing editor
 [-g, --generator]      Get generator of this feed
 [-o, --docs]           Get link to RSS documentation
 [-w, --ttl]            Get ttl, time that channel can be
                        cached before being updated
 [-b, --builddate]      Get last time the channel's
                        content changed
 [-Q, --imageurl]       Get channel image URL
 [-I, --imagetitle]     Get image title, same as ALT in html
 [-E, --imagelink]      Get link to site, image will act as a link
 [-W, --imagewidth]     Get width of image
 [-H, --imageheight]    Get height of image
 [-D, --clouddomain]    Get domain of feed update service
 [-P, --cloudport]      Get port of feed update service
 [-A, --cloudpath]      Get path to access for feed update service
 [-R, --cloudregister]  Get register procedure for feed update service
 [-O, --cloudprotocol]  Get protocol feed update service uses
 [-i, --item] INDEX     Provide index of item to display
                        If no index is provided, assume the first
                        item in the feed. All following flags will
                        be parsed as item options, till another
                        item is provided

Item options:
 [-t, --title]          Get title of item
 [-l, --link]           Get link
 [-d, --description]    Get description
 [-a, --author]         Get author
 [-C, --category]       Get category list
 [-f, --comments]       Get link to comments
 [-G, --guid]           Get GUID
 [-p, --pubdate]        Get publishing date
 [-s, --source]         Get source of item
 [-U, --enclosureurl]   Get enclosure URL
 [-T, --enclosuretype]  Get enclosure MIME type
 [-K, --enclosurelength]Get enclosure length, in bytes

General options:
 [-h, --help]           Show this message

For more information, refer to the RSS 2.0 documentation
https://validator.w3.org/feed/docs/rss2.html
```
