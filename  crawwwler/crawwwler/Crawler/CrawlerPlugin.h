#ifndef CRAWLERPLUGIN_H_
#define CRAWLERPLUGIN_H_

#include "../PluginManager/Plugin.h"
#include "../HttpUtils/HttpConnector.h"
#include "../ServerInfo/ServerInfo.h"

namespace GoldDigger
{

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
	
	// Add a server to the list of sites that this crawler must crawl, this class takes ownership of the memory
	bool AddServer(CServerInfo *pServer);
	// ### Possibly use this method
	//bool AddKeyword();
	
	// Collect all the responses from this crawl so far, the caller now owns the list and items as it is cleared from this object
	std::list<CHttpResponse*> CollectResponses();
	// Get the number of servers
	int GetNumServers() { return m_Servers.size(); };
	
	// Overridden
	virtual bool PushData(std::list<void*> Data);
private:
	// The http connector that this crawler will use to connect to the web
	CHttpConnector m_Connector;
	// The list of servers this crawler must crawl.  This class is responsible for the memory
	std::list<CServerInfo*> m_Servers;
	
	bool StartCrawl();
	// Set the next request with the resource
	bool SetRequest(std::string Resource, CHttpRequest *pRequest, CRemoteServer *pServer);
	
	// Report back on findings
	bool Announce();
};

}

#endif /*CRAWLERPLUGIN_H_*/
