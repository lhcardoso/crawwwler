// HttpResponse.h
// Represents an http response

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <list>
#include "HttpHeader.h"
#include "Url.h"

namespace Crawwwler {

class CHttpResponse {

public:
	CHttpResponse();
	// Copy constructor
	// ### Check the viability of this
	CHttpResponse(CHttpResponse &Other);
	virtual ~CHttpResponse();

	// Accessors
	// Get the result code, returns -1 if the response has not been parsed
	const int GetResultCode() const { return m_ResultCode; };
	bool IsError();

	// Set the raw response
	bool SetResponse(std::string Value);

	// Parse the entire response
	bool Parse();

	// Get the headers
	const std::list<CHttpHeader> GetHeaders() const { return m_Headers; };
	// Get the header that matches this type, returns NULL if not found. The caller is responsible for the memory
	const CHttpHeader *GetHeader(tHeaderType Type) const;

	// Get a reference to the raw result, this class still owns the memory
	const std::string *GetRawResult() const { return m_pResult; };

	// Get a copy of all the urls that have been extracted through parsing
	const std::list<CUrl> GetUrls() const { return m_Urls; };
	// Get a copy of the resources that are local to the given server
	std::list<CUrl> GetLocalUrls(std::string ServerName);

	// Set the resource that this response will represent, only set if currently empty
	bool SetResource(std::string Resource);

	const std::string GetResource() const { return m_Resource; };

private:
	// The resource that this response represents
	std::string m_Resource;

	// The response result code
	int m_ResultCode;

	// The HTTP response line
	std::string m_ResponseLine;

	// The raw unparsed result string.  This class is responsible for the memory
	std::string *m_pResult;

	// The list of extracted urls
	std::list<CUrl> m_Urls;
	// The list of extracted headers
	std::list<CHttpHeader> m_Headers;

	// Extract the headers from the list of content lines
	bool ExtractHeaders(std::list<std::string> *pLines);

};

}

#endif /*HTTPRESPONSE_H_*/
