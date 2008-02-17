#include "HttpResponse.h"

#include "../Utils/LogFile.h"
// ### Temp include for testing
//#include <fstream.h>

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Static Functions

// Split the given string into a list of line
static std::list<std::string> SplitString(const std::string& Data) {
	std::list<std::string> pResult;// = new std::list<std::string>();
	std::string n(Data);

	// Go through the string splitting out each line separated by \n
	while (!n.empty()) {
		// Find the next line
		std::string EndLine = "\r\n";
		size_t j = n.find(EndLine);
		if (j == std::string::npos) {
			//char raw[1024];
			//sprintf(raw, n.c_str());

			// The end of the document?
			std::string EmptyString;
			EmptyString.clear();
			EndLine = EmptyString;
			j = n.find(EndLine);
			if (j != std::string::npos) {
				 if (n.length() <= EmptyString.length()) {
				 	break;
				 }

			}

			// Try for just a \r
			EndLine = "\r";
			j = n.find(EndLine);
			if (j == std::string::npos) {
				// Possibly an empty line
				if (n.find("\n") == 1) {
					if (n.length() == 1) break;
					// move forward one and continue
					n = n.substr(1);
					continue;
				}
			}

		}

		// Store the line
		std::string Line = n.substr(0, n.find(EndLine));
		pResult.push_back(Line);

		// Cut the string
		size_t NewStartPos = Line.length() + EndLine.length();
		// Make sure we don't overflow the string
		if (NewStartPos >= n.length()) break;
		n = n.substr(NewStartPos);
	}

	return pResult;
}

///////////////////////////////////////////////////////////////
// Constructors

CHttpResponse::CHttpResponse() :
m_ResultCode(400) {
	m_pResult = NULL;
}

CHttpResponse::CHttpResponse(CHttpResponse &Other) :
m_ResultCode(Other.GetResultCode()) {
	m_pResult = new std::string(*Other.GetRawResult());
	// Copy the list
	std::list<CHttpHeader> Headers = Other.GetHeaders();
	for (std::list<CHttpHeader>::iterator i = Headers.begin(); i != Headers.end(); i++) {
		CHttpHeader Current = *i;
		m_Headers.push_front(Current);
	}
}

CHttpResponse::~CHttpResponse() {
	if (m_pResult) {
		delete m_pResult;
		m_pResult = NULL;
	}
}

///////////////////////////////////////////////////////////////
// Public Methods

const CHttpHeader *CHttpResponse::GetHeader(tHeaderType Type) const {
	for (std::list<CHttpHeader>::const_iterator i = m_Headers.begin(); i != m_Headers.end(); i++) {
		CHttpHeader Current = *i;
		if (Current.GetType() == Type) {
			// A match return a new object on the heap
			return new CHttpHeader(Current.GetType(), Current.GetValue());
		}
	}

	// Couldn't find it
	return NULL;
}


bool CHttpResponse::IsError() {
	// ### This will obviously have to be extended
	return m_ResultCode == 400;
}

bool CHttpResponse::SetResponse(std::string Value) {
	if (m_pResult) {
		delete m_pResult;
	}
	m_pResult = new std::string(Value);

	return true;
}

bool CHttpResponse::SetResource(std::string Resource) {
	// Only set if empty
	if (!m_Resource.empty()) return true;
	m_Resource = Resource;
	return true;
}

bool CHttpResponse::Parse() {

// Break up the file into separate lines
	std::list<std::string> pLines = SplitString(*m_pResult);

	// First extract the headers
	if (!ExtractHeaders(&pLines)) return false;

	// Parse each line
	for (std::list<std::string>::iterator i = pLines.begin(); i != pLines.end(); i++) {
		std::string Current = *i;
		int p = Current.length();

		// Ignore empty lines
		if (p < 1) continue;
		char RawRequest[1024];
		sprintf(RawRequest, Current.c_str());
		//char b[1024];
		//sprintf(b, Current.c_str());
		// Scan the line for a url
		std::string HRef = "href=";
		size_t Pos = Current.find(HRef);
		if (Pos == std::string::npos) {
			// No url on this line, ignore
			continue;
		}

		// Move to the end of href="
		Pos += HRef.length() + 1;

		// Find the next "
		int EndPos = Current.find("\"", Pos);

		// Now extract the url
		std::string Url = Current.substr(Pos, EndPos - Pos);
		// Don't save empty urls
		if (Url.empty()) continue;
		// ### For now don't save mailto:
		std::string MailTo = "mailto:";
		if (Url.find(MailTo) == 0) continue;
		if (Url.find("styles") != std::string::npos) continue;
		if (Url.find("http://www.google") == 0) continue;
		if (Url.find(".css") == (Url.length() - 3)) continue;

		// Add to the list of extracted urls
		CUrl CurrentUrl;
		// Parse the url and add it to the list
		if (CurrentUrl.Parse(Url)) {
			m_Urls.push_back(CurrentUrl);
		}
	}

	return true;
}

std::list<CUrl> CHttpResponse::GetLocalUrls(std::string ServerName) {
	std::list<CUrl> Result;

	// Nothing to do if we don't have any urls at all
	if (m_Urls.size() <= 0) return Result;

	// The urls should already be parsed
	for (std::list<CUrl>::iterator i = m_Urls.begin(); i != m_Urls.end(); i++) {
		CUrl Current = *i;
		// Check if this represents a local url
		if (Current.IsLocal()) {
			Result.push_back(Current);
			continue;
		}
		// Alternatively, the servername could match
		if (Current.MatchesServer(ServerName)) {
			Result.push_back(Current);
			continue;
		}
	}
	return Result;

}

///////////////////////////////////////////////////////////////
// Private Methods

bool CHttpResponse::ExtractHeaders(std::list<std::string> *pLines) {

	// Make sure our list of headers is empty
	m_Headers.clear();

	// Run through the lines extracting headers until the end of the headers is reached
	while (true) {
		std::string Current = pLines->front();
		// This could be the HTTP header
		if (Current.find("HTTP") == 0) {
			m_ResponseLine = Current;
			pLines->pop_front();
			continue;
		}
		// Try to parse this line as a header
		CHttpHeader Header;
		if (!Header.Parse(Current)) {

			// Reached the end of the headers
			break;
		}

		// Add it to the list of headers
		m_Headers.push_back(Header);
		// Remove it from the input list
		pLines->pop_front();

	}

	return true;
}

}
