#include "RemoteServer.h"

#include "../RobotsTxt/RobotsTxtFile.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CRemoteServer::CRemoteServer() {
}
///// server base class must own a port
CRemoteServer::~CRemoteServer() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CRemoteServer::SetServer(std::string ServerUrl) {
	// ### Need to do some checks
	if (!m_Url.Parse(ServerUrl)) return false;
	return true;
}

std::string CRemoteServer::ToString() {
	return m_Url.GetServer();
}

std::string CRemoteServer::HostName() {
	return m_Url.GetServer();
}


///////////////////////////////////////////////////////////////
// Private Methods



}
