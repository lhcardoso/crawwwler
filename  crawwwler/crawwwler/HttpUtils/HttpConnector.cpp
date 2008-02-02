#include "HttpConnector.h"

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "RemoteServer.h"
#include "../ServerInfo/ServerInfo.h"
#include "Socket.h"

namespace GoldDigger
{

CHttpConnector::CHttpConnector() {
}

CHttpConnector::~CHttpConnector() {
	
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CHttpConnector::SendRequest(	CRemoteServer Server,
									const CHttpRequest& Request,
									CHttpResponse **ppResponse) {
	// Create the socket
	CSocket Socket;
	return Socket.SendRequest(Server.ToString(), Server.GetPort().GetPortNum(), Request, ppResponse);
	
}

}
