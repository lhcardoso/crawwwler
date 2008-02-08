// RemoteServer.h
// Represents a remote server that will be crawled

#ifndef REMOTESERVER_H_
#define REMOTESERVER_H_

#include "Server.h"
#include <string>
#include <list>
#include "Url.h"

namespace Crawwwler {
	
class CRobotsTxtFile;

class CRemoteServer: public CServer {
public:
	CRemoteServer();
	virtual ~CRemoteServer();
	
	// The fully qualified server name
	const std::string ToString() const;
	// The host name only of the url
	std::string HostName();
	
	// Set the server by name, fails if the string is completely incorrect
	bool SetServer(std::string ServerUrl);
	
	
	
private:
	// The server url
	CUrl m_Url;
};

}

#endif /*REMOTESERVER_H_*/
