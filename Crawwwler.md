## Introduction ##

Crawwwler is a large scale open source web crawler.  It is currently in its very beginning stages of development.

## Design (so far) ##

At the top level, there is a crawler manager.  All plugins are instantiated, initialised and started here.  Each plugin then runs completely independantly of its siblings.

Plugins can subscribe to the output of other plugins.  Once a plugin is ready to report back on its data, it goes through its list of subscribers and passes data directly to it as an Object, thus leaving the manager with very little throughput.  The subscriber is ready for this data and castes it from type Object to the type it knows it will be receiving from the sending plugin.  This allows generic subscription to output, which must be handled by the subscriber.

To illustrate, currently there are to plugins: a CCrawlerPlugin and a CUrlExtractor.  The CCrawlerPlugin is given a list of server names to crawl.  It sends a request to that server for, in effect, it's 'index.html' page.  Once the CCrawlerPlugin has gone through the list of servers and downloaded the respective index/default pages it reports back.

The manager has ensured that the CUrlExtractor has already subscribed to the output of the CCrawlerPlugin by passing a the CUrlExtractor**to the CCrawlerPlugin's list of subscribers.**

The CCrawlerPlugin then effectively invokes a function in the CUrlExtractor to pass it information about the servers and the downloaded pages.  The CUrlExtractor extracts all the urls from the index pages (currently on local to the current server) and passes back to the CCrawlerPlugin a new list of specific pages that need to be crawled on the server .

## TODO ##

Ah, well I mean come on.  There's so much that needs to be done.  First in line however is the design of the data store, now that a basic prototype has been implemented.  The data store will probably be in the form of a MySQL database (another plugin which will subscribe to the output of the CCrawlerPlugin :-) ).

## Ideas ##

Please feel free to let us know any ideas you have or caveats of which you are aware.  Email to: crawwwler@mynameisfury.co.uk

## Warning ##

Always obey ROBOTS.TXT!!!

This is obviously a **very dangerous** toy to let loose on the WWW.  Please be extremely careful if you use this code.  Test it on a site hosted on your local machine or server that you own.  Its not currently meant to crawl anything other than your test site, but the testing thus far has been limited.  So be careful!!!

## Get Involved ##

Of course, and with pleasure! If you're interested, take a look at the code in its current state and send an email to: crawwwler@mynameisfury.co.uk