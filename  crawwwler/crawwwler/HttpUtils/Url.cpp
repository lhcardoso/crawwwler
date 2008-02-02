#include "Url.h"

namespace GoldDigger
{
 
// Determine whether the given string represents a single digit
static bool IsDigit(std::string Value) {
	if (Value.length() != 1) return false;
	if (Value == "0") return true;
	if (Value == "1") return true;
	if (Value == "2") return true;
	if (Value == "3") return true;
	if (Value == "4") return true;
	if (Value == "5") return true;
	if (Value == "6") return true;
	if (Value == "7") return true;
	if (Value == "8") return true;
	if (Value == "9") return true;
	
	return false;
}

///////////////////////////////////////////////////////////////
// Constructors

CUrl::CUrl() {
	m_Scheme = "";
	m_Username = "";
	m_Password = "";
	m_Resource = "";
	m_ServerName = "";
	m_PortNumber = -1;
	m_bHasWWW = false;
}

CUrl::~CUrl() {
}

///////////////////////////////////////////////////////////////
// Public Methods

std::string CUrl::ToString() {
	std::string Result;
	
	Result.append(m_Scheme);
	if (m_bHasWWW) {
		Result.append("www.");
	}
	Result.append(m_ServerName);
	if (!Result.empty()) {
		Result.append("/");
	}
	
	if (!m_Resource.empty()) {
		Result.append(m_Resource);
	}
	if (!m_Arguments.empty()) {
		Result.append("?");
		Result.append(m_Arguments);
	}
	return Result;
}

bool CUrl::Parse(std::string Value) {
	// Take a copy of the value
	std::string Val = Value;
	//char *pCurrent;
	//strcpy(pCurrent, Val.c_str());
//	In general, URLs are written as follows:

//      <scheme>:<scheme-specific-part>
       
    // If this is a fully qualified url, there will be a scheme
    
//	3.1. Common Internet Scheme Syntax
//
//   While the syntax for the rest of the URL may vary depending on the
//   particular scheme selected, URL schemes that involve the direct use
//   of an IP-based protocol to a specified host on the Internet use a
//   common syntax for the scheme-specific data:
//
//       //<user>:<password>@<host>:<port>/<url-path>
    
    // Helper variable for determining whether we have already obtained the servername
    bool bGotServer = false;
    
	// Ordering is important here
	
	
	// Get rid of relative links
	if (Value.find("../") == 0) {
		while (Value.find("../") == 0) {
			Value = Value.substr(3);
			m_Resource = Value;
			return true;
		}
	}
	// First get rid of arguments
	if (!ParseArguments(&Val)) return false;
	// Try to parse the scheme
	// Remember if we got a scheme
	bool bHasScheme = false;
	if (!ParseScheme(&Val, &bHasScheme)) return false;
	if (bHasScheme) {
		// The entire parse is now complete
		return true;
	}
	
	// There was no scheme
	
	// Take off the port, if any
    	if (!ParsePort(&Val)) return false;
    	
   
    	
    	// Look for the "www"
	size_t Pos = Val.find("www"); 
	if (Pos != std::string::npos) {
		// If at this stage the "www" is not at the beginning, this is an error
		if (Pos != 0) return false;
		// "www" must be followed by "."
		size_t PosOfDot = 3;
		if (Val.substr(3, 1) != ".") return false;
		
		// We have "www"
		m_bHasWWW = true;
		
		// Cut out "www."
		size_t NewStartPos = PosOfDot + 1;
		Val = Val.substr(NewStartPos);
		
		// Get the servername
		if (!ParseServerName(&Val)) return false;
		
		// All thats left now is the resource
		m_Resource = Val;
		return true;
	}
	
	// As of this point
	// ports are gone
	// www is gone
    // scheme is gone
    // username and password are gone
    
	// At this stage we are left with the following as a possiblity
	// servername.co.uk[0*("/"Directory)"/"] filename.ext
	
	
	
	// [servername.co.uk][0*("/"Directory)"/"] filename.ext

	
	
	// If we find a "/" then we have either a servername or a directory
	Pos = Val.find("/");
	if (Pos != std::string::npos) {
		if (Pos != 0) { 			
			// If we find a "." first then this first part is a servername
			size_t PosOfDot = Val.find(".");
			if (PosOfDot < Pos) {
				if (!ParseServerName(&Val)) return false;
				// All thats left now is the resource
				m_Resource = Val;
				return true;
			}		
		}
	}
	
	// No slashes
	// At this stage we are left with either a servername or a filename
	
	// ### Below there are problems regarding directories and local servers
	// From a link in a web page a path could refer to a local network server OR a directory and
	// it is impossible to tell.  Will probably have to put them into a "special" bucket and then test
	// But for now we'll ignore local servers and assume directories
	
	// No "." means a local server
	if (Val.find(".") == std::string::npos) {
		m_ServerName = Val;
		// Remember that we have already go the server
		bGotServer = true;
		// Nothing else left, successful parse :-)
		// This is one special case that is definitely a local server!!
		return true;
	}
	
	// Still either a servername or filename
	// Problems are that both a filename and server could have .com
	
	// Store these separately for now
   	if (!ParseConfusing(&Val)) return false;
        
	// All false returns should have been handled inside the loop, so this means success!
	return true;
}

bool CUrl::ParseScheme(std::string *pValue, bool *pbHasScheme) {
	m_Scheme = "";
	// We don't have a scheme yet
	*pbHasScheme = false;
	
	size_t Pos = pValue->find("://"); 
	if (Pos == std::string::npos) {
		// Nothing to do, this is fine
		return true;
	} 
	
	// This is a <scheme>
	m_Scheme = pValue->substr(0, Pos - 1);
	// Cut of the first part e.g "http://"
	size_t NewStartPos = Pos + 3;
	*pValue = pValue->substr(NewStartPos);
	
	Pos = pValue->find("www"); 
	if (Pos != std::string::npos) {
		// If at this stage the "www" is not at the beginning, this is an error
		if (Pos != 0) return false;
		// "www" must be followed by "."
		size_t PosOfDot = 3;
		if (pValue->substr(3, 1) != ".") return false;
		
		// We have "www"
		m_bHasWWW = true;
		
		// Cut out "www."
		size_t NewStartPos = PosOfDot + 1;
		*pValue = pValue->substr(NewStartPos);
	}
    		
    		
	// Carry on parsing the rest of the url
	// ### could have a password!!!!! do that here!
	if (!ParseUnamePwd(pValue)) return false;
	if (!ParsePort(pValue)) return false;
	if (!ParseServerName(pValue)) return false;
	// Now we only have a resource
	m_Resource = *pValue;
	
	*pbHasScheme = true;
	
	return true;
}

bool CUrl::ParseServerName(std::string *pValue) {
	size_t Pos = pValue->find("/");
	
	if (Pos != std::string::npos) {
		m_ServerName = pValue->substr(0, Pos);
		// Strip out the servername only (not the "/", then continue as there could be multiple "/"
		*pValue = pValue->substr(Pos + 1);
	} else {
		m_ServerName = *pValue;
		*pValue = "";
	}
	
	return true;
}

// Check against known extensions
static bool IsServer(std::string Ext) {
	
	if (Ext.length() == 2) {
		// Testing will tell if 2 letters is not a safe stopping point to assume a server
		return true;
	}
	
	// This is the really confusing one, but we'll assume "com" is a server, not a windows executable
	if (Ext == "com") return true;
	if (Ext == "net") return true;
	if (Ext == "org") return true;
	if (Ext == "gov") return true;
	if (Ext == "bitnet") return true;
	if (Ext == "edu") return true;
	
	// Not a known extension
	return false;
}
bool CUrl::ParseConfusing(std::string *pValue) {
	// Find the last "."
	size_t Pos = pValue->find(".");
	if (Pos == std::string::npos) return false;
	
	size_t CurrentPos = Pos;
	while (Pos != std::string::npos) {
		CurrentPos = Pos;
		// Iterate through the "."
		Pos = pValue->find(".", Pos + 1);
	}
	
	// This is the last ".", check against the string that comes after it
	Pos = CurrentPos;
	std::string Val = pValue->substr(Pos + 1);
	
	if (IsServer(Val)) {
		m_ServerName = *pValue;
	} else {
		m_Resource = *pValue;
	}
	
	return true;
}


bool CUrl::ParseArguments(std::string *pValue) {
	m_Arguments = "";
	size_t Pos = pValue->find("?");
	if (Pos == std::string::npos) {
		// Nothing to do
		return true;
	}
	// Set the arguments, we don't care what they are
	m_Arguments = pValue->substr(Pos + 1);
	
	// Cut off the arguments and continue parsing
	*pValue = pValue->substr(0, Pos);
	
	return true;
}

bool CUrl::ParsePort(std::string *pValue) {
	
	m_PortNumber = -1;
	size_t Pos = pValue->find(":");
	if (Pos == std::string::npos) return true;
	
	size_t CurrentPos = Pos + 1;
	bool bNumFound =  false;
	while (IsDigit(pValue->substr(CurrentPos, 1))) {
		bNumFound = true;
		CurrentPos++;
	}
	// Move back to the last digit
	CurrentPos--;
	if (!bNumFound) {
		// Should have found a port number, this is an error
		return false;
	}
	
	// Extract the port number
	size_t Len = CurrentPos - (Pos + 1);
	std::string NumString = pValue->substr(Pos + 1, Len);
	m_PortNumber = atoi(NumString.c_str());
	
	// Cut out the port number, we can continue parsing the rest of the string
	std::string FirstPart = "";
	// if the ":" was not at the beginning then we must remember the first part
	if (Pos > 0) {
		FirstPart = pValue->substr(0, Pos);
	}
	
	// Get the part after the port number
	std::string SecondPart = "";
	// There is a second part if the port number was not the end of the string
	if (CurrentPos > pValue->length()) {
		SecondPart = pValue->substr(Pos + 1);
	}
	
	// Concatenate the first and second parts
	*pValue = FirstPart.append(SecondPart);
	
	return true;
}

bool CUrl::ParseUnamePwd(std::string *pValue) {
	size_t Pos = pValue->find(":");
	if (Pos == std::string::npos) return true;
	// This a <password>, there MUST be a username before it
	if (Pos == 0) {
		// There is no username before the password, this is an error
		return false;
	}
	m_Username = pValue->substr(0, Pos);
	// Move past the ":" ready to read the password
	*pValue = pValue->substr(Pos + 1);
	
	// Set Pos to be the already found "@"
	Pos = pValue->find("@");
	m_Password = pValue->substr(0, Pos);
	// Move past the "@" ready to parse the rest of the url
	*pValue = pValue->substr(Pos + 1);
	
	return true;
}


}
