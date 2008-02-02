// Url.h
// Represents a url according to the rfc at
// http://www.ietf.org/rfc/rfc1738.txt


#ifndef URL_H_
#define URL_H_

#include <string>

namespace GoldDigger
{

class CUrl
{
public:
	CUrl();
	virtual ~CUrl();
	
	bool Parse(std::string Value);
	std::string GetResource() { return m_Resource; };
	std::string GetServer() { return m_ServerName; };
	
	// Determine if this url represents a local resource
	bool IsLocal() { return m_ServerName.empty(); };
	// Determine if this url matches the given servername
	bool MatchesServer(std::string ServerName) { return m_ServerName == ServerName; };
	
	std::string ToString();
	
private:
	// The resource represented by this url
	std::string m_Resource;
	
	// The scheme e.g http or webcal
	std::string m_Scheme;
	// The arguments, we don't care about these, just want to remember them
	std::string m_Arguments;
	
	// The optional <username>
	std::string m_Username;
	// The optional <password>
	std::string m_Password;
	
	// The optional port number
	int m_PortNumber;
	
	// Whether this has www. portion
	int m_bHasWWW;
	
	// The servername eg server or server.com
	std::string m_ServerName;
	
	
	// Try to parse the arguments pass via a url
	bool ParseArguments(std::string *pValue);
	// Try to parse the username and password part of a url
	bool ParseUnamePwd(std::string *pValue);
	// Try to parse the port portion of a url
	bool ParsePort(std::string *pValue);
	bool ParseScheme(std::string *pValue, bool *pbHasScheme);
	bool ParseServerName(std::string *pValue);
	// Sometimes we reach a single name.ext and nothing else url
	// This could often be either a filename or a server
	// We'll use a list of known extensions to check for each for now
	// until a better strategy is in place
	// unsure names will be placed in a special bucket for inspection
	bool ParseConfusing(std::string *pValue);
};

}

#endif /*URL_H_*/
