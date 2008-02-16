#include "HttpClient.h"

#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/Url.h"
#include "../HttpUtils/Port.h"
#include "../HttpUtils/Socket.h"
#include "../HttpUtils/HttpRequest.h"
#include "../GlobalData/GlobalData.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CHttpClient::CHttpClient() {
}

CHttpClient::~CHttpClient() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CHttpClient::GetResource(const CUrl& Url, const CCPort& Port, CHttpResponse *pResponse) const {
	// Check args
	if (!pResponse) return false;

	// Build the request
	CHttpRequest Request;
	if (!SetRequest(Url.GetServer(), Url.GetResource(), &Request))

	// Send it off
	// This stupid thing won't compile if I delete CSocket r. Try it!!!
	CSocket r;
	CSocket Socket;

	return Socket.SendRequest(Url.GetServer(), Port.GetPortNum(), Request, pResponse);
}

bool CHttpClient::SetRequest(const std::string& ServerName, const std::string& Resource, CHttpRequest *pRequest) const {
	// Check parameters
	if (!pRequest) return false;

	// This is an Http GET request
	pRequest->SetType(REQUEST_GET);

	// Headers
	{
		// The user agent
		std::string UserAgent(GlobalData::CRAWLER_NAME);
		tHeaderType HeaderType = HEADER_USER_AGENT;
		CHttpHeader UserAgentHeader(HeaderType, UserAgent);
		if (!pRequest->AddHeader(UserAgentHeader)) return false;

		// The host
		HeaderType = HEADER_HOST;
		CHttpHeader HostHeader(HeaderType, ServerName);
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
	}

	// Set the target resource
	pRequest->SetResource(Resource);

	// Success
	return true;
}

///////////////////////////////////////////////////////////////
// Private Methods

}
