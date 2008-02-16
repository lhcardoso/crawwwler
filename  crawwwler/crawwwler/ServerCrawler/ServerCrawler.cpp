#include "ServerCrawler.h"

#include "../HttpConnector/HttpClient.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/Url.h"
#include "../HttpUtils/Port.h"
#include "../RobotsTxt/RobotsTxtFile.h"
#include "../Url/ManagedUrlList.h"
#include "../UrlExtractor/UrlExtractor.h"

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

bool CServerCrawler::Crawl(const std::string& ServerName) {
	// The http client we'll use to send the request
	CHttpClient HttpClient;

	// Get the robots.txt file
	CHttpResponse RawRobotsFile;

	CUrl Url;
	std::string ThisServer(ServerName);
	ThisServer = ThisServer.append("/robots.txt");
	if (!Url.Parse(ThisServer)) return false;
	CCPort Port(80);
	if (!HttpClient.GetResource(Url, Port, &RawRobotsFile)) {
		// This means a complete failure to fetch a robots file!!!
		return false;
	}

	// Process the robots file
	CRobotsTxtFile RobotsFile;
	if (!RobotsFile.Parse(RawRobotsFile)) return false;

	// Start crawling from the index page
	CManagedUrlList Urls;
	{
		CUrl IndexUrl;
		std::string ServerNameCopy(ServerName);
		if (!IndexUrl.Parse(ServerNameCopy.append("/"))) return false;
		Urls.AddUnique(IndexUrl);
	}

	// Recursively crawl the site
	while (!Urls.IsEmpty()) {
		// Crawl the current target
		CUrl *pCurrent = Urls.GetNext();
		if (!pCurrent) {
			// This is an error since Urls.IsEmpty() should have returned false
			return false;
		}

		// Make sure the robots file allows this
		if (!RobotsFile.Allows(*pCurrent)) {
			delete pCurrent;
			pCurrent = NULL;
			continue;
		}

		// Crawl the current target
		CHttpResponse Response;
		if (!HttpClient.GetResource(*pCurrent, CCPort(80), &Response)) {
			// Skip this one
			continue;
		}

		// Extract the urls from this response
		CManagedUrlList ExtractedUrls;
		CUrlExtractor UrlExtractor;
		if (!UrlExtractor.ExtractFrom(Response, &ExtractedUrls)) {

		}

		// Add uniquely to the managed list of urls
		Urls.AddUnique(ExtractedUrls);
	}

	// Successful crawl
	return true;
}


///////////////////////////////////////////////////////////////
// Private Methods



}
