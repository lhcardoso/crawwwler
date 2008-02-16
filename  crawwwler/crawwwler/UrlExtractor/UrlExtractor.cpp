#include "UrlExtractor.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/Url.h"
#include "../Url/ManagedUrlList.h"


namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CUrlExtractor::CUrlExtractor()
{
}

CUrlExtractor::~CUrlExtractor()
{
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CUrlExtractor::Start() {

	// Nothing to do if we have no data, which is fine
	if (m_ServerData.size() == 0) return true;
	// Process the data for each server in the list
	for (std::list<CServerInfo*>::iterator i = m_ServerData.begin(); i != m_ServerData.end(); i++) {
		CServerInfo *pServerInfo = *i;
		if (!ProcessServer(pServerInfo)) {
			// Need to do something, continue is no good
			return false;
		}
		// This server now probably has new resources to crawl
		int ServerResources = pServerInfo->GetResourceCount();
		if (ServerResources > 0) {
			pServerInfo->NewResources();
		}
	}

	if (!Announce()) return false;



	// We're done with our data
	m_ServerData.clear();

	// Success :-)
	return true;

}

bool CUrlExtractor::ExtractFrom(CHttpResponse& File, CManagedUrlList* pList) {
	// Parse the raw response
	if (!File.Parse()) {
		// Ignore this one??
		// ### Can't really do this, though it could mean there is no raw response!!!
		return false;
	}

	// Add all unique urls (not in-page duplicates) exposed by this response
	std::list<CUrl> Urls = File.GetUrls();
	for (std::list<CUrl>::iterator i = Urls.begin(); i != Urls.end(); i++) {
		pList->AddUnique(*i);
	}
	// Go through the list of discovered resources. Add the local ones to the list of pages to retrieve
	// and the remote ones, well, the remote ones
	//std::string ServerName = pServerInfo->GetServerName();
	//std::list<CUrl> LocalUrls = pCurrent->GetLocalUrls(ServerName);
	//if (!pServerInfo->EmptyResources()) return false;
	//if (!pServerInfo->AddNewUrls(LocalUrls)) return false;

	return true;
}

bool CUrlExtractor::PushData(std::list<void*> Data) {

	// Copy the data since, the caller still owns it
	for (std::list<void*>::iterator i = Data.begin(); i != Data.end(); i++) {
		// ### Use of the copy constructor!!!
		CServerInfo *pCurrent = (CServerInfo*)*i;
		m_ServerData.push_back(pCurrent);
	}

	return true;
}

///////////////////////////////////////////////////////////////
// Private Methods

bool CUrlExtractor::ProcessServer(CServerInfo *pServerInfo) {

	// Get hold of the responses
	std::list<CHttpResponse*> *pResponses = pServerInfo->GetResponses();
	// Parse each response and remember that we have already visited that resource
	for (std::list<CHttpResponse*>::iterator i = pResponses->begin(); i != pResponses->end(); i++) {
		CHttpResponse *pCurrent = *i;

		// Parse the raw response
		if (!pCurrent->Parse()) {
			// Ignore this one??
			// ### Can't really do this, though it could mean there is no raw response!!!
			return false;
		}

		// Remember that we have already crawled this page
		const CHttpHeader *pLocationHeader = pCurrent->GetHeader(HEADER_CONTENT_LOCATION);
		if (!pLocationHeader) {
			// We might not have received a content location header so just use the resource we set
			char ab[100];
			sprintf(ab, pCurrent->GetResource().c_str());
			pLocationHeader = new CHttpHeader(HEADER_CONTENT_LOCATION, pCurrent->GetResource());
			if (!pLocationHeader) return false;
		}

		// Delete this temporary copy of the header
		delete pLocationHeader;
		pLocationHeader = NULL;
	}

	// Clear the list of resources to visit
	if (!pServerInfo->ClearTargetResources()) return false;

	// Process the newly discovered resources
	if (!ProcessNewResources(pResponses, pServerInfo)) return false;

	// Empty the responses
	pServerInfo->EmptyResponses();

	return true;
}

bool CUrlExtractor::Announce() {
	// Nothing to do if there is no data, which is fine
	if (m_ServerData.size() == 0) return true;

	// Convert the CServerInfo list to a void list
	std::list<void*> Data;
	for (std::list<CServerInfo*>::iterator i = m_ServerData.begin(); i != m_ServerData.end(); i++) {
		CServerInfo* pCurrent = *i;
		// Don't add if there are no resources
		if (!pCurrent->HasResources()) continue;
		Data.push_back(*i);
	}

	// Let each of the subscribers know about our findings
	for (std::list<CPlugin*>::iterator i = m_Subscribers.begin(); i != m_Subscribers.end(); i++) {
		CPlugin* pCurrent = *i;
		// ### This should be a pointer to a list else it will be way too slow
		if (!pCurrent->PushData(Data)) return false;
	}

	return true;
}


bool CUrlExtractor::ProcessNewResources(std::list<CHttpResponse*> *pResponses, CServerInfo *pServerInfo) {
	// Add the discovered resources from each response to the list of resources that need to be crawled
	for (std::list<CHttpResponse*>::iterator i = pResponses->begin(); i != pResponses->end(); i++) {
		CHttpResponse *pCurrent = *i;

		// Go through the list of discovered resources. Add the local ones to the list of pages to retrieve
		// and the remote ones, well, the remote ones
		std::string ServerName = pServerInfo->GetServerName();
		std::list<CUrl> LocalUrls = pCurrent->GetLocalUrls(ServerName);
		if (!pServerInfo->EmptyResources()) return false;
		if (!pServerInfo->AddNewUrls(LocalUrls)) return false;
	}
	return true;
}

}
