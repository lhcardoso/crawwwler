// CrawlerPlugin.h

#ifndef CRAWLERPLUGIN_H_
#define CRAWLERPLUGIN_H_

#include <map>
#include "../PluginManager/Plugin.h"
#include "../DomainCrawler/DomainCrawlerList.h"
#include "../Url/ManagedUrlList.h"

namespace Crawwwler {
using namespace std;

class CRemoteServer;
class CHttpResponse;

class CCrawlerManager : public CPlugin {
public:
	CCrawlerManager();
	virtual ~CCrawlerManager();

	//Overridden
	bool Init();
	//Overridden
	bool Start();
	//Overridden
	bool Stop();

private:
	// Run the plugin constantly, call Start
	void Crawl();
	// Run one cycle i.e crawl m_CurrentUrls
	bool RunCycle();

	// Prepare the list of current urls to crawl in this cycle
	bool PrepareNextCycle();
	// Sort the list of new urls into matching domain for the next cycle
	bool PrepareDomains();

	// Whether we have been asked to stop crawling
	bool m_bStopRequest;

	// The list of domains we are currently crawling
	map<std::string, CDomainCrawler*, DomainCmp> m_CurrentDomains;
	// The list of new urls we have been given to crawl
	CManagedUrlList m_NewUrls;

};

}

#endif /*CRAWLERPLUGIN_H_*/
