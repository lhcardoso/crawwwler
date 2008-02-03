// ServerInfo.h
// Represents known information about a remote server and its data 

#ifndef SERVERINFO_H_
#define SERVERINFO_H_

#include "../HttpUtils/RemoteServer.h"
#include "../HttpUtils/HttpResponse.h"

namespace Crawwwler {

class CServerInfo
{
public:
	// This class takes ownership of the server
	CServerInfo();
	virtual ~CServerInfo();
	
	// Set the server, returns false if this class already has a server
	bool SetServer(CRemoteServer *pServer);
	// Get a pointer to this server
	CRemoteServer *GetServer();
	// Get the server name represented by this object
	std::string GetServerName() { return m_pServer->HostName(); };
	
	// Add a response to the list of known responses, this class takes ownership of the memory
	bool AddResponse(CHttpResponse *pResponse);
	// Get a reference to the responses which this class still owns
	std::list<CHttpResponse*> *GetResponses();
	
	// Add more urls that need to be crawled, this will only add new urls local to this server
	bool AddNewUrls(std::list<CUrl> Urls);
	// Add an already visited resource
	bool AddVisitedResource(CUrl Resource);
	int GetVisitedResourceCount() { return m_VisitedResources.size(); };
	
	// Get the next resource from the list and remove it from the list
	// Returns false if no more resources are needed from this server
	bool PopResource(std::string *pResource);
	
	int GetResourceCount() { return m_Resources.size(); };
	bool HasResources() { return !m_Resources.empty(); };
	void NewResources() { m_bResourcesExhausted = false; };
	void EmptyResponses() { m_Responses.clear(); };
	bool EmptyResources() { m_Resources.clear(); return true; };
	int GetResponsesCount() { return m_Responses.size(); }; 
	
	// Clear the last of resources to visit
	bool ClearTargetResources() { m_Resources.clear(); return true; };

private:
	void operator=(CServerInfo& Other);
	// The remote server whose data this class represents
	CRemoteServer *m_pServer;
	// The responses collected as a result of a crawl.  This class is responsible for the memory
	std::list<CHttpResponse*> m_Responses;
	
	// The associated list of resources to fetch from this server.
	// This list can start off as empty which will assume we're starting a crawl i.e "/"
	// The list is then populated during a crawl
	std::list<std::string> m_Resources;	
	
	// The list of resources on this server that have already been visited
	std::list<CUrl> m_VisitedResources;
	
	// The associated robots.txt file
	CRobotsTxtFile *pRobotsFile;
	
	// Whether all the resources have been exhausted from this server
	bool m_bResourcesExhausted;
	
	// Whether a url has already been visited
	bool AlreadyVisited(CUrl Url);
	// Whether a url has already been targeted as a "to visit" resource
	bool AlreadyTargeted(CUrl Url);
	
	
	
};

}

#endif /*SERVERINFO_H_*/
