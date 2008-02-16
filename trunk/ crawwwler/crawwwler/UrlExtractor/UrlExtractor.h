// UrlExtractor.h
// Plugin for extracting Urls from an in memory representation of an html file

#ifndef URLEXTRACTOR_H_
#define URLEXTRACTOR_H_

#include "../PluginManager/Plugin.h"
#include "../ServerInfo/ServerInfo.h"

namespace Crawwwler {

class CUrlExtractor : public CPlugin {
public:
	CUrlExtractor();
	virtual ~CUrlExtractor();

	// Overridden
	virtual bool Init() { return true; };
	// Overridden
	virtual bool Start();
	// Overridden
	virtual bool Stop() { return true; };
	// Overridden
	virtual bool PushData(std::list<void*> Data);

	//////////////////////////////////
	// New implementation starts here

	// Extract all the urls from this http response and populate pList with them
	bool ExtractFrom(CHttpResponse& File, class CManagedUrlList* pList);

private:
	std::list<CServerInfo*> m_ServerData;

	// Process the data for this server
	bool ProcessServer(CServerInfo *pServerInfo);

	// Report back on findings
	bool Announce();

	// Process all the newly discovered resources
	bool ProcessNewResources(std::list<CHttpResponse*> *pResponses, CServerInfo *pServerInfo);
};

}

#endif /*URLEXTRACTOR_H_*/
