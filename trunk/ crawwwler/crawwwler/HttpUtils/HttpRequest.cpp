#include "HttpRequest.h"

namespace GoldDigger
{

///////////////////////////////////////////////////////////////
// Static Functions

static std::string RequestTypeToString(tRequestType Type) {
	switch (Type) {
		case REQUEST_GET:
			return "GET";
		case REQUEST_POST:
			return "POST";
		default:
			return "";
	}
	return "";
}

static std::string ResourceToString(std::string Resource) {
	if (Resource.length() == 0) return "/";
	// Make sure it starts with "/"
	std::string NewResource("");
	if (Resource.length() > 1) {
		if (Resource.find("/") != 0) {
			NewResource.append("/");
		}
			
	}
	NewResource.append(Resource);
	return NewResource;
}

///////////////////////////////////////////////////////////////
// Constructors

CHttpRequest::CHttpRequest() {
	m_RequestType = REQUEST_INVALID;
}

CHttpRequest::~CHttpRequest() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CHttpRequest::AddHeader(CHttpHeader Header) {
	m_Headers.push_back(Header);
	return true;
}

void CHttpRequest::SetResource(std::string Resource) { 	
	m_Resource = Resource;
}

std::string CHttpRequest::GetRawRequest() {
	std::string Result;
	
	// First line
	{
		// First the request type
		Result.append(RequestTypeToString(m_RequestType));
		if (Result.length() == 0) return "fff";
		Result.append(" ");
		
		// Then the resource
		Result.append(ResourceToString(m_Resource));
		Result.append(" ");
		
		// Http Version
		// ### upgrade to 1.1
		Result.append("HTTP/1.1");
		// End the line
		Result.append("\n");
	}
	
	// Headers
	{
		// Add each of the headers
		for (std::list<CHttpHeader>::iterator i = m_Headers.begin(); i != m_Headers.end(); i++) {
			CHttpHeader Current = *i;
			Result.append(Current.ToString());
			Result.append("\n");
		}
	}
	
	// Close off the request
	Result.append("\n\n");
	
	return Result;
}

}
