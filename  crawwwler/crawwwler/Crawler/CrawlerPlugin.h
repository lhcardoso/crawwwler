// CrawlerPlugin.h
// ### Currently not implemented

#ifndef CRAWLERPLUGIN_H_
#define CRAWLERPLUGIN_H_

#include "../PluginManager/Plugin.h"

namespace Crawwwler {

class CRemoteServer;
class CHttpResponse;

class CCrawlerPlugin : public CPlugin {
public:
	CCrawlerPlugin();
	virtual ~CCrawlerPlugin();

	//Overridden
	bool Init();
	//Overridden
	bool Start();
	//Overridden
	bool Stop();

private:

};

}

#endif /*CRAWLERPLUGIN_H_*/
