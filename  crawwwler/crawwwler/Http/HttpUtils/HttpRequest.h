#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string>
#include <list>
#include "HttpHeader.h"
#include "../../Server/RemoteServer.h"

namespace Crawwwler {

	// Types of http requests
	enum tRequestType {
		REQUEST_GET = 1,
		REQUEST_POST,
		REQUEST_INVALID
	};

class CHttpRequest
{
public:
	CHttpRequest();
	virtual ~CHttpRequest();

	// Set the type of this request
	void SetType(tRequestType Type) { m_RequestType = Type; };
	// Add a header to this request
	bool AddHeader(CHttpHeader Header);
	// Set the resource that will be requested
	void SetResource(std::string Resource);
	// Get the resource
	const std::string GetResource() const { return m_Resource; };

	// Get the full ready-to-send raw request
	std::string GetRawRequest();

private:
	// The type of request
	tRequestType m_RequestType;
	// The list of headers held by this request
	std::list<CHttpHeader> m_Headers;

	// The resource that will be requested
	std::string m_Resource;

	// ### todo: request data
};

}

#endif /*HTTPREQUEST_H_*/
