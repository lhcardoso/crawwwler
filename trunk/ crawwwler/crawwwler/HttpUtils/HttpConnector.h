// HttpConnector.h

// Represents an http connection


#ifndef HTTPCONNECTOR_H_
#define HTTPCONNECTOR_H_

namespace GoldDigger
{

class CSocket;
class CHttpResponse;

class CHttpConnector
{
public:
	CHttpConnector();
	virtual ~CHttpConnector();
	
	// Send an http request, true on success and the parsed response is then returned
	bool SendRequest(	class CRemoteServer Server,
						const class CHttpRequest& Request,
						CHttpResponse **ppResponse); 
	
private:
	//CSocket *m_pSocket;
};

}

#endif /*HTTPCONNECTOR_H_*/
