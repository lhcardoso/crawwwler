#include "CrawlerPlugin.h"

#include <iostream>
#include "../HttpUtils/RemoteServer.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/HttpRequest.h"
#include "../GlobalData/GlobalData.h"
#include "../HttpUtils/HttpHeader.h"

namespace Crawwwler
{

///////////////////////////////////////////////////////////////
// Constructors

CCrawlerPlugin::CCrawlerPlugin() {
}

CCrawlerPlugin::~CCrawlerPlugin() {
	// Delete each of the servers
	while (!m_Servers.empty()) {
		CServerInfo *pCurrent = m_Servers.front();
		m_Servers.pop_front();
		delete pCurrent;
		pCurrent = NULL;
	}

}

///////////////////////////////////////////////////////////////
// Public Methods

bool CCrawlerPlugin::Init() {
	// Not yet implemented
	return false;
}

bool CCrawlerPlugin::Start() {
	// Pass on the call
	return StartCrawl();
}

bool CCrawlerPlugin::Stop() {
	// Not yet implemented
	return false;
}

bool CCrawlerPlugin::AddServer(CServerInfo *pServer) {
	// Add the server to the front of the list
	// ### Possibly will be the end, testing will tell
	m_Servers.push_front(pServer);
	return true;
}

std::list<CHttpResponse*> CCrawlerPlugin::CollectResponses() {
	// ### This method will eventually need to be thread safe, but, erm, how? In, fact this whole class will probably have to be thread safe.

	std::list<CHttpResponse*> Result;

	// Make a copy of the all reposnses for each of the servers
	for (std::list<CServerInfo*>::iterator i = m_Servers.begin(); i != m_Servers.end(); i++) {
		CServerInfo *pCurrent = *i;
		std::list<CHttpResponse*> *pResponses = pCurrent->GetResponses();

		// Copy all the responses for this server
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
	// ### This is wrong since we will be able to add servers from time to time and this class should just wait
	if (m_Servers.size() == 0) return false;

	// Crawl through all required resources on each server
	for (std::list<CServerInfo*>::iterator i = m_Servers.begin(); i != m_Servers.end(); i++) {
		CServerInfo *pCurrent = *i;

		// Crawl all resources on this server
		std::string Resource;
		while (pCurrent->PopResource(&Resource)) {
			// Build the request
			CHttpRequest Request;
			{
				// Set the request
				if (false) {
					// Couldn't set the request so ignore this server
					continue;
				}
			}

			// Send the request to this server. Create the object on the heap so that the serverinfo can take ownership
			CHttpResponse *pResponse = new CHttpResponse();


			if (false) {
				// ### Might have to register a failure reason and the fact that the request wasn't successful
				delete pResponse;
				pResponse = NULL;
				continue;
			}

			// Associate the response received with the resource requested
			if (!pResponse->SetResource(Resource)) return false;

			// Store the response
			if (!pCurrent->AddResponse(pResponse)) return false;
			// pCurrent now has ownership
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

bool CCrawlerPlugin::Announce() {

	// Nothing to do if there is no data, which is fine
	if (m_Servers.size() == 0) return true;

	// Convert the CServerInfo list to a void list
	std::list<void*> Data;
	for (std::list<CServerInfo*>::iterator i = m_Servers.begin(); i != m_Servers.end(); i++) {
		// Is this a copy or a new pointer to the original??
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
