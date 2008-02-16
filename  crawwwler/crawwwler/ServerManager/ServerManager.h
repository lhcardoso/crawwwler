// ServerCrawler.h
// Manages the crawling of a remote server

#ifndef SERVERMANAGER_H_
#define SERVERMANAGER_H_

#include "../HttpUtils/RemoteServer.h"

namespace Crawwwler
{

class CServerCrawler {
public:
	CServerCrawler();
	virtual ~CServerCrawler();

	bool Crawl();

private:
	CServerCrawler(const CServerCrawler& Other);
	CServerCrawler& operator=(const CServerCrawler& Rhs);

	// Server name to crawl
	std::string Servername;



};

}

#endif /*SERVERMANAGER_H_*/
