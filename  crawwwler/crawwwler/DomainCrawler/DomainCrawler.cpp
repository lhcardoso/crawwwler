#include "DomainCrawler.h"

#include "../HttpConnector/HttpClient.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/Url.h"
#include "../HttpUtils/Port.h"
#include "../RobotsTxt/RobotsTxtFile.h"
#include "../Url/ManagedUrlList.h"
#include "../UrlExtractor/UrlExtractor.h"
#include <fstream.h>

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Static Methods

// whether the url matches the domain name
static bool MatchesDomain(const CUrl& Url, const std::string& DomainName) {
	// Does the domain name match
	if (Url.MatchesServer(DomainName)) {
		return true;
	}
	// Points to another domain
	return false;
}

///////////////////////////////////////////////////////////////
// Constructors

CDomainCrawler::CDomainCrawler() {
}

CDomainCrawler::~CDomainCrawler() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CDomainCrawler::Crawl(const std::string& DomainName) {
	// Get a copy of the argument so we can change it
	std::string DomainNameCopy(DomainName);

	// The http client we'll use to send the request
	CHttpClient HttpClient;

	// Get the robots.txt file
	CHttpResponse RawRobotsFile;

	CUrl Url;
	std::string ThisServer(DomainName);
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
		if (!IndexUrl.Parse(DomainNameCopy.append("/"))) return false;
		Urls.AddUnique(IndexUrl);
	}

	// Recursively crawl the site
	while (!Urls.IsEmpty()) {
		// Crawl the current target
		const CUrl *pCurrent = Urls.Pop();

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
			// This is actually an error
			continue;
		}

		// Add all new urls that belong to this domain to the list
		for (std::list<CUrl>::iterator i = ExtractedUrls.begin(); i != ExtractedUrls.end(); i++) {
			CUrl Current(*i);
			// If its a relative link, inject the servername
			if (Current.IsLocal()) {
				std::string QualifiedUrl(DomainNameCopy);
				DomainNameCopy.append(Current.ToString());
				// Reparse
				if (!Current.Parse(QualifiedUrl)) continue;
			}

			if (!MatchesDomain(Current, DomainName)) continue;
			// Add to the list
			Urls.AddUnique(Current);
		}

		// Save the page to disk
		// ### Temporary!! This should be done elsewhere
		if (!SaveFile(&Response)) return false;
	}

	// Successful crawl
	return true;
}


///////////////////////////////////////////////////////////////
// Private Methods

bool CDomainCrawler::SaveFile(const CHttpResponse *pResponse) {
	// Get the location header to use as part of the filename
	const CHttpHeader *pLocationHeader = pResponse->GetHeader(HEADER_CONTENT_LOCATION);
	// If we did not receive a content location header just use the resource we set
	if (!pLocationHeader) {
		pLocationHeader = new CHttpHeader(HEADER_CONTENT_LOCATION, pResponse->GetResource());
		if (!pLocationHeader) return false;
	}
	// The url is needed to build a filename
	std::string Location = pLocationHeader->GetValue();
	delete pLocationHeader;
	pLocationHeader = NULL;
	CUrl Url;
	if (!Url.Parse(Location)) return false;

	// ### Hard coded path, change yours
	std::string s("/home/dave/data/");

	// The filename is the name of the resource
	std::string temp(Url.GetResource());
	while (temp.find("/") != std::string::npos) {
		temp = temp.substr(temp.find("/") + 1);
	}
	s.append(temp);

	// Save to disk
	ofstream f(s.c_str());
	f << pResponse->GetRawResult()->c_str();
	f.close();
	return true;
}

}
