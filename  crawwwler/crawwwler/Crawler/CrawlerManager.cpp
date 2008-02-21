#include "CrawlerManager.h"

#include "../Http/HttpUtils/HttpResponse.h"
#include "../Http/HttpUtils/HttpRequest.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Static Functions


///////////////////////////////////////////////////////////////
// Constructors

CCrawlerManager::CCrawlerManager() {
	m_bStopRequest = false;
}

CCrawlerManager::~CCrawlerManager() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CCrawlerManager::Init() {
	m_bStopRequest = false;
	// Not yet implemented
	return false;
}

bool CCrawlerManager::Start() {

	// ### Start the new thread here
	Crawl();

	// Not yet implemented
	return false;
}

bool CCrawlerManager::Stop() {
	// Not yet implemented
	return false;
}


///////////////////////////////////////////////////////////////
// Private Methods

void CCrawlerManager::Crawl() {

	// Run until we've had a stop request
	while (!m_bStopRequest) {
		// Prepare for the current cycle
		if (!PrepareNextCycle()) {
			// ### Put thread.sleep code here
			return;
		}

		if (!RunCycle()) {
			// ### Put thread.sleep code here
			return;
		}
	}
}

bool CCrawlerManager::RunCycle() {


	// Crawl the domains and collect all the responses we can
	CHttpResponseList Responses;
	for (map<std::string, CDomainCrawler*>::iterator i = m_CurrentDomains.begin(); i != m_CurrentDomains.end(); i++) {
		CDomainCrawler *pCurrent = i->second;

		// Crawl the current urls for this domain
		if (!pCurrent->CrawlCurrentUrls()) {
			// ### Do something if we couldn't crawl
		}

		// Pop all the responses from this crawler onto the list we're collecting
		{
			Responses.AddResponses(pCurrent->GetResponses());
			pCurrent->DeleteResponses();
		}
	}

	// TODO Announce findings (Responses) and pass them on to the subscribing url extractor if we can
	return true;
}

bool CCrawlerManager::PrepareNextCycle() {
	// If we currently have domains to crawl, then we're done
	if (!m_CurrentDomains.empty()) return true;

	// If there are no new urls then we're also done
	if (m_NewUrls.empty()) return true;

	// Sort all the urls into matching domains
	if (!PrepareDomains()) return false;

	// Done!
	return true;
}

bool CCrawlerManager::PrepareDomains() {
	// The domain list should be empty
	m_CurrentDomains.clear();

	// No good if there are no new urls
	if (m_NewUrls.empty()) return false;

	// Sort the url into domains
	for (std::list<CUrl>::iterator i = m_NewUrls.begin(); i != m_NewUrls.end(); i++) {
		CUrl CurrentUrl(*i);
		std::string ServerName = CurrentUrl.GetServer();

		// Check to see if we've already got a crawler for this domain
		map<std::string, CDomainCrawler*>::iterator Pos = m_CurrentDomains.find(ServerName);
		if (Pos != m_CurrentDomains.end()) {
			// We've already got a crawler for this domain just push in the url
			(Pos->second)->AddUrl(CurrentUrl);
			continue;
		}
		// We don't have a crawler for this domain yet, so add one
		CDomainCrawler *pDomainCrawler = new CDomainCrawler(ServerName);
		pDomainCrawler->AddUrl(CurrentUrl);
		// Insert into the map
		m_CurrentDomains.insert(make_pair(ServerName, pDomainCrawler));
		// Don't delete since the map now owns the memory
	}

	return false;
}

} // namespace GoldDigger
