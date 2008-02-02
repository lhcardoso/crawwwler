#include "ServerInfo.h"
#include <iostream>

namespace GoldDigger
{

///////////////////////////////////////////////////////////////
// Constructors

CServerInfo::CServerInfo() {
	m_pServer = NULL;
	m_bResourcesExhausted = false;
	pRobotsFile = NULL;
}

CServerInfo::~CServerInfo() {
	if (m_pServer) {
		delete m_pServer;
		m_pServer = NULL;
	}
	// TODO delete the list of responses!!!!
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CServerInfo::SetServer(CRemoteServer *pServer) {
	m_pServer = pServer;
	return true;
}

CRemoteServer *CServerInfo::GetServer() {
	return m_pServer;
}

bool CServerInfo::AddResponse(CHttpResponse *pResponse) {
	m_Responses.push_back(pResponse);
	return true;
}

std::list<CHttpResponse*> *CServerInfo::GetResponses() {
	return &m_Responses;
}

bool CServerInfo::AddNewUrls(std::list<CUrl> Urls) {
	for (std::list<CUrl>::iterator i = Urls.begin(); i != Urls.end(); i++) {
		CUrl Current = *i;
		
		// Check that its not in the list of known urls and that it has not been visited already
		if (AlreadyTargeted(Current)) continue;
		if (AlreadyVisited(Current)) continue;
	
		// New resource, add to the list
		m_Resources.push_back(Current.GetResource());
	}
	return true;
}

bool CServerInfo::AddVisitedResource(CUrl Resource) {
	
	// Check that its not in the list of known urls
	if (AlreadyVisited(Resource)) {
		// This is okay, just don't add it
		return true;
	}
	
	// Add it to the list of visited resources
	m_VisitedResources.push_back(Resource);
	
	return true;
}

bool CServerInfo::PopResource(std::string *pResource) {
	if (!pResource) return false;
	// Clear the string
	pResource->clear();
	
	// If we don't have a robots.txt file yet, ignore everything else
	// ### Temporarily commented out until the robots parser is in place
	//if (!pRobotsFile) {
	//	*pResource = "/robots.txt";
	//	return true;
	//}
	
	// Nothing to do if all resources have already been exhausted
	if (m_bResourcesExhausted) return false;
	
	// If we haven't got any resources yet, then an initial resource is needed and nothing more
	// so allow callers to think resources are, for now, exhausted
	if (m_Resources.size() <= 0) {
		*pResource = "/";
		m_bResourcesExhausted = true;
		return true;
	}
	
	// Get the first available resource
	*pResource = m_Resources.front();
	char d[1024];
	sprintf(d, pResource->c_str());
	// Remove it from the list
	m_Resources.pop_front();
	
	return true;
}


///////////////////////////////////////////////////////////////
// Private Methods

bool CServerInfo::AlreadyVisited(CUrl Url) {
	
	for (std::list<CUrl>::iterator i = m_VisitedResources.begin(); i != m_VisitedResources.end(); i++) {
		CUrl Current = *i;
		if (Current.GetResource() == Url.GetResource()) {
			return true;
		}
	}
	
	return false;
}

bool CServerInfo::AlreadyTargeted(CUrl Url) {
	// Check that this url has not already been visited
	for (std::list<std::string>::iterator j = m_Resources.begin(); j != m_Resources.end(); j++) {
		std::string Current = *j;
		if (Url.GetResource() == Current) return true;
	}
	
	// Didn't find it in the list
	return false;
}
}
