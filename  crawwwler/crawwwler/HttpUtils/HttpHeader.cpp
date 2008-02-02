#include "HttpHeader.h"

namespace GoldDigger
{
	
///////////////////////////////////////////////////////////////
// Constructors

CHttpHeader::CHttpHeader() {
	m_Type = HEADER_INVALID;
}

CHttpHeader::CHttpHeader(tHeaderType Type, std::string Value) :
m_Value(Value) {
	m_Type = Type;
	m_Field = TypeAsString(Type);
}

CHttpHeader::~CHttpHeader() {
}

///////////////////////////////////////////////////////////////
// Public Methods


std::string CHttpHeader::TypeAsString(tHeaderType Type) {
	switch (Type) {
		case HEADER_RESULT_OK:
			return "HTTP/1.1 200 OK";
		case HEADER_USER_AGENT:
			 return "User-Agent";
		case HEADER_ACCEPT_TYPE:
			return "Accept";
		case HEADER_ACCEPT_LANG:
			return "Accept-Language";
		case HEADER_ACCEPT_ENCODING:
			return "Accept-Encoding";
		case HEADER_HOST:
			return "Host";
		case HEADER_PROXY_CONNECTION:
			return "Proxy-Connection";
		case HEADER_PRAGMA:
			return "Pragma";
		case HEADER_CONNECTION:
			return "Connection";
		case HEADER_CONTENT_LOCATION:
			return "Content-Location";
		case HEADER_CONTENT_TYPE:
			return "Content-Type";
		case HEADER_SERVER:
			return "Server";
		case HEADER_DATE:
			return "Date";
		case HEADER_ACCEPT_RANGES:
			return "Accept-Ranges";
		case HEADER_LAST_MODIFIED:
			return "Last-Modified";
		case HEADER_CONTENT_LENGTH:
			return "Content-Length";
		case HEADER_INVALID:
			return "InvalidHeader";
		default:
			return "";
	}
}

tHeaderType CHttpHeader::StringAsType(std::string Value) {
	if (Value == "HTTP/1.1 200 OK") return HEADER_RESULT_OK;
	if (Value == "User-Agent") return HEADER_USER_AGENT;
	if (Value == "Accept") return HEADER_ACCEPT_TYPE;
	if (Value == "Accept-Language") return HEADER_ACCEPT_LANG;
	if (Value == "Accept-Encoding")	return HEADER_ACCEPT_ENCODING;
	if (Value == "Host") return HEADER_HOST;
	if (Value == "Proxy-Connection") return HEADER_PROXY_CONNECTION;
	if (Value == "Pragma") return HEADER_PRAGMA;
	if (Value == "Connection") return HEADER_CONNECTION;
	if (Value == "Content-Location") return HEADER_CONTENT_LOCATION;
	if (Value == "Content-Type") return HEADER_CONTENT_TYPE;
	if (Value == "Server") return HEADER_SERVER;
	if (Value == "Date") return HEADER_DATE;
	if (Value == "Accept-Ranges") return HEADER_ACCEPT_RANGES;
	if (Value == "Last-Modified") return HEADER_LAST_MODIFIED;
	if (Value == "Content-Length") return HEADER_CONTENT_LENGTH;
	
	return HEADER_INVALID;
}

bool CHttpHeader::Parse(std::string Value) {
	
	size_t Pos = Value.find(":");
	
	// If there is no colon ":" then this is definitely not a headers
	if (Pos == std::string::npos) return false;
	
	// TODO Try to match the part before the colon to a known header type
	
	 
	std::string Field = Value.substr(0, Pos);
	if (Field.length() == 0) return false;
	
	// TODO set the header type
	m_Type = StringAsType(Field);
	
	// Set the field
	m_Field = Field;
	Value = Value.substr(Pos + 1);
	while (Value.find(" ") == 0) {
		Value = Value.substr(1);
	}
	
	char d[1024];
	sprintf(d, Value.c_str());
	// Set the value
	m_Value = Value;
	
	return true;
	
	
}

std::string CHttpHeader::ToString() {
	// Format is Field:Value
	
	std::string Response("");
	
	// Append the type
	Response.append(m_Field);
	//Response.append(TypeAsString(m_Type));
	
	// Must have a header type
	if (Response.length() == 0) return "";
	
	Response.append(":");
	Response.append(m_Value);
	
	return Response;
} 

}
