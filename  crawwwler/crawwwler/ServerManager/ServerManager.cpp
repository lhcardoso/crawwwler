#include "ServerManager.h"

namespace Crawwwler
{

///////////////////////////////////////////////////////////////
// Constructors

CServerCrawler::CServerCrawler() {
}

CServerCrawler::~CServerCrawler() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CServerCrawler::Crawl() {
	// Get the robots.txt file
	CHttpResponse RawRobotsFile = m_HttpClient.Crawl("robots.txt");

	// Process the robots file
	CRobotsTxtFile RobotsFile(RawRobotsFile);

	// Start crawling from the index page
	CManagedUrlList Urls;
	Urls.Add("/");

	// Recursively crawl the site
	while (!Urls.Empty()) {
		// Crawl the current target
		CUrl Current = GetNext();

		// Make sure the robots file allows this
		if (!RobotsFile.Allows(Current)) {
			continue;
		}

		// Crawl the current target
		CHttpResponse Response = m_HttpClient.Crawl(Current);
		// Extract the urls from this response
		std::list<CUrl> ExtractedUrls = m_UrlExtractor.ExtractFrom(Response);

		// Add uniquely to the managed list of urls
		Urls.Add(ExtractedUrls);
	}

	// Successful crawl
}


///////////////////////////////////////////////////////////////
// Private Methods



}
