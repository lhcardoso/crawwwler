// Server.h

// Base class for local and remote servers

#ifndef SERVER_H_
#define SERVER_H_

#include "Port.h"

namespace Crawwwler {

class CServer
{
public:
	CServer();
	virtual ~CServer();
	
	const CCPort GetPort() const { return m_Port; };
	
private:
	// The port associated with this server
	CCPort m_Port;	
};

}

#endif /*SERVER_H_*/
