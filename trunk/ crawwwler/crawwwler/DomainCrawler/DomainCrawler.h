// ServerCrawler.h
// Manages the crawling of a remote server

#ifndef DOMAINCRAWLER_H_
#define DOMAINCRAWLER_H_

#include "../Server/RemoteServer.h"
#include "../RobotsTxt/RobotsTxtFile.h"
#include "../Http/HttpConnector/HttpClient.h"
#include "../Url/ManagedUrlList.h"
#include "../Http/HttpUtils/HttpResponseList.h"

namespace Crawwwler {

// Struct for comparing lookups in a map of CDomainCrawler
struct DomainCmp {
	bool operator()(const std::string& Lhs, const std::string& Rhs) const {
		return strcmp(Lhs.c_str(), Rhs.c_str()) < 0;
	}
};

class CDomainCrawler {
public:
	CDomainCrawler(const std::string& DomainName);
	virtual ~CDomainCrawler();

	// Crawl the given managed list of urls and return the response
	bool CrawlCurrentUrls();
	// Add a Url to the current list of urls to be crawled
	bool AddUrl(const CUrl& Url);

	// Access to and removal of responses
	const CHttpResponseList& GetResponses() const { return m_Responses; };
	// ### If CHttpResponseList ever changes to hold pointers, we'll have to delete them here
	void DeleteResponses() { m_Responses.clear(); };

private:
	// This is used but should be fine using the default
	//CDomainCrawler(const CDomainCrawler& Other);
	CDomainCrawler& operator=(const CDomainCrawler& Rhs);

	// Fetch the robots file
	bool FetchRobotsFile();

	// Save the http response to a file on disk
	// ### This is here for testing purposes only and will be removed
	bool SaveFile(const class CHttpResponse *pResponse);

	// The domain name that this crawler will crawl
	std::string m_DomainName;

	// The robots file that the domain uses
	CRobotsTxtFile m_RobotsFile;

	// The http client for fetching resource
	CHttpClient m_HttpClient;

	// The managed list of urls to be crawled
	CManagedUrlList m_CurrentUrls;

	// A list of responses from recent crawls that have not yet been collected by third party
	CHttpResponseList m_Responses;

};

}

#endif /*DOMAINCRAWLER_H_*/
