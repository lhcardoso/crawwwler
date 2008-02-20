#include "DomainCrawler.h"

#include "../Http/HttpUtils/HttpResponse.h"
#include "../NetworkAPI/Port.h"
#include "../Url/Url.h"
#include "../UrlExtractor/UrlExtractor.h"
// ### Temp include while testing
#include <fstream.h>

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Static Methods

///////////////////////////////////////////////////////////////
// Constructors

CDomainCrawler::CDomainCrawler(const std::string& DomainName) : m_DomainName(DomainName) {
}

CDomainCrawler::~CDomainCrawler() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CDomainCrawler::FetchRobotsFile() {
	// Build the url for a robots.txt file
	CUrl Url;
	std::string RobotsUrl(m_DomainName);
	RobotsUrl.append("/robots.txt");
	if (!Url.Parse(RobotsUrl)) return false;

	// Fetch the robots file
	CHttpResponse RawRobotsFile;
	if (!m_HttpClient.GetResource(Url, CCPort(80), &RawRobotsFile)) {
		// This means a complete failure to fetch a robots file!!!
		return false;
	}

	// Process the robots file
	if (!m_RobotsFile.Parse(RawRobotsFile)) return false;

	return true;
}

bool CDomainCrawler::CrawlCurrentUrls() {

	// Get a copy of the domain name so we can append various url string to it
	std::string DomainNameCopy(m_DomainName);

	// Recursively crawl the site
	while (!m_CurrentUrls.IsEmpty()) {
		// Crawl the current target
		const CUrl *pCurrent = m_CurrentUrls.Pop();

		if (!pCurrent) {
			// This is an error since Urls.IsEmpty() should have returned false
			return false;
		}

		// Make sure the robots file allows this
		if (!m_RobotsFile.Allows(*pCurrent)) {
			delete pCurrent;
			pCurrent = NULL;
			continue;
		}

		// Crawl the current target
		CHttpResponse Response;
		if (!m_HttpClient.GetResource(*pCurrent, CCPort(80), &Response)) {
			// Skip this one
			delete pCurrent;
			pCurrent = NULL;
			continue;
		}

		// Add the response to the out return value
		m_Responses.AddResponse(Response);

		// Extract the urls from this response
		//CManagedUrlList ExtractedUrls;
		//CUrlExtractor UrlExtractor;
		//if (!UrlExtractor.ExtractFrom(Response, &ExtractedUrls)) {
		//	// This is actually an error
		//	delete pCurrent;
		//	pCurrent = NULL;
		//	continue;
		//}

		// Save the page to disk
		// ### Temporary!! This should be done elsewhere
		if (!SaveFile(&Response)) {
			delete pCurrent;
			pCurrent = NULL;
			return false;
		}

		delete pCurrent;
		pCurrent = NULL;
	}

	// Successful crawl

	return true;
}

bool CDomainCrawler::AddUrl(const CUrl& Url) {
	m_CurrentUrls.AddUnique(Url);
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
