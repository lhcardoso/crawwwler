// Socket.h

// Represents a socket for network communications

#ifndef SOCKET_H_
#define SOCKET_H_

#include <string> 

#include <netdb.h>
namespace GoldDigger
{


class CHttpRequest;
class CHttpResponse;
//class CRemoteServer;

class CSocket
{
public:
	CSocket();
	virtual ~CSocket();
	
	// Send a request through the socket, returns true on success and returns a CHttpResponse object through the parameter
	bool SendRequest(std::string ServerName, int PortNumber, const CHttpRequest& Request, CHttpResponse **ppResponse);
	
private:
	bool Send(std::string ServerName, int PortNumber, CHttpRequest Request, std::string* pResult);

};

}

#endif /*SOCKET_H_*/