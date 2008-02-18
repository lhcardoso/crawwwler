// ServerCrawler.h
// Manages the crawling of a remote server

#ifndef DOMAINCRAWLER_H_
#define DOMAINCRAWLER_H_

#include "../Server/RemoteServer.h"

namespace Crawwwler
{

class CDomainCrawler {
public:
	CDomainCrawler();
	virtual ~CDomainCrawler();

	bool Crawl(const std::string& DomainName);

private:
	CDomainCrawler(const CDomainCrawler& Other);
	CDomainCrawler& operator=(const CDomainCrawler& Rhs);

	// Save the http response to a file on disk
	// ### This is here for testing purposes only and will be removed
	bool SaveFile(const class CHttpResponse *pResponse);
};

}

#endif /*DOMAINCRAWLER_H_*/
