#include "UrlExtractor.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/Url.h"
#include <fstream.h>
#include <iostream>

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
		ofstream p("/home/dave/be.txt");
		p << pCurrent->GetRawResult()->c_str();
		p.close();
		CHttpHeader *pLocationHeader = pCurrent->GetHeader(HEADER_CONTENT_LOCATION);
		if (!pLocationHeader) {
			// We might not have received a content location header so just use the resource we set
			char ab[100];
			sprintf(ab, pCurrent->GetResource().c_str());
			pLocationHeader = new CHttpHeader(HEADER_CONTENT_LOCATION, pCurrent->GetResource());
			if (!pLocationHeader) return false;
		}
		bool bResult = ProcessVisitedResource(*pLocationHeader, pServerInfo); 
		
		// Delete this temporary copy of the header
		delete pLocationHeader;
		pLocationHeader = NULL;
		
		if (!bResult) return false;
	}
	
	// Clear the list of resources to visit
	if (!pServerInfo->ClearTargetResources()) return false;

	// Process the newly discovered resources
	if (!ProcessNewResources(pResponses, pServerInfo)) return false;
	
	// Empty the responses
	pServerInfo->EmptyResponses();
	
	// TODO add to the list of parsed responses
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
bool CUrlExtractor::SaveFile(CHttpResponse *pResponse, CUrl Url) {
	std::string s("/home/dave/data/");
	std::string temp(Url.GetResource());
	char e[200];
	sprintf(e, temp.c_str());
	while (temp.find("/") != std::string::npos) {
		temp = temp.substr(temp.find("/") + 1);
	}
	s.append(temp);
	char d[1024];
	sprintf(d, s.c_str());
	ofstream f(s.c_str());
	f << pResponse->GetRawResult()->c_str();
	f.close();
	return true;
}

bool CUrlExtractor::ProcessVisitedResource(CHttpHeader LocationHeader, CServerInfo* pServerInfo) {
	
	// First Get the content location directory	
	CUrl Url;
	if (!Url.Parse(LocationHeader.GetValue())) return false;
	
	// Add this page to the already visited
	if (!pServerInfo->AddVisitedResource(Url)) return false;
		
	return true;
}

bool CUrlExtractor::ProcessNewResources(std::list<CHttpResponse*> *pResponses, CServerInfo *pServerInfo) {
	// Add the discovered resources from each response to the list of resources that need to be crawled
	for (std::list<CHttpResponse*>::iterator i = pResponses->begin(); i != pResponses->end(); i++) {
		CHttpResponse *pCurrent = *i;
		
		// Save the page to disk
		// ### Temporary!! This should be done elsewhere
		CHttpHeader *pLocationHeader = pCurrent->GetHeader(HEADER_CONTENT_LOCATION);
		if (!pLocationHeader) {
			// We might not have received a content location header so just use the resource we set
			char ab[100];
			sprintf(ab, pCurrent->GetResource().c_str());
			pLocationHeader = new CHttpHeader(HEADER_CONTENT_LOCATION, pCurrent->GetResource());
			if (!pLocationHeader) return false;
		}
		std::string Location = pLocationHeader->GetValue();
		delete pLocationHeader;
		pLocationHeader = NULL;
		CUrl Url;
		if (!Url.Parse(Location)) return false;
		
		if (!SaveFile(pCurrent, Url)) return false;
			
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
