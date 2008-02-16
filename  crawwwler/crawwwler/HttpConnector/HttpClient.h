// HttpClient.h
// A simple http client to get resources from a server

#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

namespace Crawwwler {

class CHttpClient {
public:
	CHttpClient();
	virtual ~CHttpClient();

	// Try to get the resource, returns false on web failure, not incorrect resource. Raw response is returned via pResponse
	bool GetResource(const class CUrl& Url, const class CCPort& Port, class CHttpResponse *pResponse) const;
};

}

#endif /*HTTPCLIENT_H_*/
