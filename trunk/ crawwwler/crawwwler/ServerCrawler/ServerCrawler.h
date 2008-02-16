// ServerCrawler.h
// Manages the crawling of a remote server

#ifndef SERVERCRAWLER_H_
#define SERVERCRAWLER_H_

#include "../HttpUtils/RemoteServer.h"

namespace Crawwwler
{

class CServerCrawler {
public:
	CServerCrawler();
	virtual ~CServerCrawler();

	bool Crawl(const std::string& ServerName);

private:
	CServerCrawler(const CServerCrawler& Other);
	CServerCrawler& operator=(const CServerCrawler& Rhs);
};

}

#endif /*SERVERCRAWLER_H_*/
