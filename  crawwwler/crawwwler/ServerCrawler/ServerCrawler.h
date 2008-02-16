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

	// Save the http response to a file on disk
	// ### This is here for testing purposes only and will be removed
	bool SaveFile(const class CHttpResponse *pResponse);
};

}

#endif /*SERVERCRAWLER_H_*/
