// CrawlerPlugin.h
// ### Currently not implemented

#ifndef CRAWLERPLUGIN_H_
#define CRAWLERPLUGIN_H_

#include "../PluginManager/Plugin.h"
#include "../Url/Url.h"

namespace Crawwwler {

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

	// Crawl a domain, instructed to do so by passing a 'servername/' url
	bool CrawlDomain(const CUrl& Url);
	// Crawl for a specific resource, instructed to do so by passing a url pointing to a specific resource in a domain
	bool CrawlResource(const CUrl& Url);

	// Prepare the list of current urls to crawl in this cycle
	bool PrepareNextCycle();

	// Whether we have been asked to stop crawling
	bool m_bStopRequest;

	// The list of urls for the current cycle
	std::list<CUrl> m_CurrentUrls;
	// The stand by list of target urls for the next cycle
	std::list<CUrl> m_TargetUrls;

};

}

#endif /*CRAWLERPLUGIN_H_*/
