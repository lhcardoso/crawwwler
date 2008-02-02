#include "CrawlerPlugin.h"

#include <iostream>
#include "../HttpUtils/RemoteServer.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/HttpRequest.h"
#include "../GlobalData/GlobalData.h"
#include "../HttpUtils/HttpHeader.h"

namespace GoldDigger
{

///////////////////////////////////////////////////////////////
// Constructors

CCrawlerPlugin::CCrawlerPlugin() : m_Connector() {
}

CCrawlerPlugin::~CCrawlerPlugin() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CCrawlerPlugin::Init() {
	return false;
}

bool CCrawlerPlugin::Start() {
	// Pass on the call
	return StartCrawl(); 
}

bool CCrawlerPlugin::Stop() {
	return false;
}

bool CCrawlerPlugin::AddServer(CServerInfo *pServer) {
	m_Servers.push_front(pServer);
	return true;
}

std::list<CHttpResponse*> CCrawlerPlugin::CollectResponses() {
	// ### This method will eventually need to be thread safe, but, erm, how?
	
	std::list<CHttpResponse*> Result;
	
	// Copy the list across
	for (std::list<CServerInfo*>::iterator i = m_Servers.begin(); i != m_Servers.end(); i++) {
		CServerInfo *pCurrent = *i;
		std::list<CHttpResponse*> *pResponses = pCurrent->GetResponses();
		
		for (std::list<CHttpResponse*>::iterator i = pResponses->begin(); i != pResponses->end(); i++) {
			CHttpResponse *pCurrentResponse = *i;
			Result.push_back(pCurrentResponse);
		}
		
		
		// Don't delete pCurrent because it is now owned by the caller
	}
	
	// Clear the list
	m_Servers.clear();
	
	return Result;
}

bool CCrawlerPlugin::PushData(std::list<void*> Data) {
	
	// Copy the data since, the caller still owns it
	for (std::list<void*>::iterator i = Data.begin(); i != Data.end(); i++) {
		// ### Use of the copy constructor!!!
		CServerInfo *pCurrent = (CServerInfo*)*i;
		m_Servers.push_back(pCurrent);
	}
	
	return true;
}

///////////////////////////////////////////////////////////////
// Private Methods

bool CCrawlerPlugin::StartCrawl() {
	// If there are no servers to crawl, then there is nothing to do
	// ### This is wrong since we will be able to add servers from time to time
	if (m_Servers.size() == 0) return false;
	
	// Go through the list of servers
	int numServers = m_Servers.size();
	for (std::list<CServerInfo*>::iterator i = m_Servers.begin(); i != m_Servers.end(); i++) {
		CServerInfo *pCurrent = *i;
		
		// The CServerInfo class maintains ownership
		CRemoteServer *pServer = pCurrent->GetServer();
		
		// Go through each resource
		std::string Resource;
		while (pCurrent->PopResource(&Resource)) {
			// Build the request
			CHttpRequest Request;
			{
				// Set the request
				if (!SetRequest(Resource, &Request, pServer)) {
					// Couldn't set the request so ignore this server
					continue;
				}
			}
			
			// Send the request to this server. Create the object on the heap so that the serverinfo can take ownership
			CHttpResponse *pResponse = new CHttpResponse();
			
			
			if (!m_Connector.SendRequest(*pServer, Request, &pResponse)) {
				// ### Might have to register a failure reason and the fact that the request wasn't successful
				continue;
			}
			// Remember the resource we are trying to get
			if (!pResponse->SetResource(Resource)) return false;
			// Store the response
			if (!pCurrent->AddResponse(pResponse)) return false;
			// pCurrent now has ownership
			char pp[200];
			sprintf(pp, Resource.c_str());
			pResponse = NULL;
		}
		
		// Don't delete pCurrent since we still need it
		pCurrent = NULL;
	}
	
	// Report back on findings
	if (!Announce()) return false;
	// Clear the list of servers, by now they are somebody elses responsibility
	m_Servers.clear();
	
	// Successful crawl!
	return true;
}

bool CCrawlerPlugin::SetRequest(std::string Resource, CHttpRequest *pRequest, CRemoteServer *pServer) {
	// Check parameters
	if (!pRequest) return false;
	
	// Request Type
	pRequest->SetType(REQUEST_GET);
	
	// Headers
	
	// The user agent
	std::string UserAgent(GlobalData::CRAWLER_NAME);
	tHeaderType HeaderType = HEADER_USER_AGENT;
	CHttpHeader UserAgentHeader(HeaderType, UserAgent);
	if (!pRequest->AddHeader(UserAgentHeader)) return false;
	
	// The host
	HeaderType = HEADER_HOST;
	CHttpHeader HostHeader(HeaderType, pServer->HostName());
	if (!pRequest->AddHeader(HostHeader)) return false;
	
	HeaderType = HEADER_PROXY_CONNECTION;
	CHttpHeader ProxyHeader(HeaderType, "Keep-Alive");
	if (!pRequest->AddHeader(ProxyHeader)) return false;
	
	HeaderType = HEADER_PRAGMA;
	CHttpHeader PragmaHeader(HeaderType, "no-cache");
	if (!pRequest->AddHeader(PragmaHeader)) return false;
	
	HeaderType = HEADER_CONNECTION;
	CHttpHeader ConnectionHeader(HeaderType, "close");
	if (!pRequest->AddHeader(ConnectionHeader)) return false;
	
	
	pRequest->SetResource(Resource);
	char d[1024];
	sprintf(d, pRequest->GetRawRequest().c_str());
	return true;
}

bool CCrawlerPlugin::Announce() {
	
	// Nothing to do if there is no data, which is fine
	if (m_Servers.size() == 0) return true;
	
	// Convert the CServerInfo list to a void list
	std::list<void*> Data;
	for (std::list<CServerInfo*>::iterator i = m_Servers.begin(); i != m_Servers.end(); i++) {
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


} // namespace GoldDigger
