// RobotsTxtFile.h

// In-memory representation of a robots.txt file as per http://www.robotstxt.org/norobots-rfc.txt
// Not yet implemented

#ifndef ROBOTSTXTFILE_H_
#define ROBOTSTXTFILE_H_

namespace Crawwwler {

class CRobotsTxtFile
{
public:
	CRobotsTxtFile();
	virtual ~CRobotsTxtFile();

	// Try to parse the robots file from a raw http response
	bool Parse(const class CHttpResponse& RawFile);

	// Whether the rules laid out by this robots file allows a the current url to be parsed
	// Will return false if not or if wrong server
	bool Allows(const class CUrl& Url);
};

}

#endif /*ROBOTSTXTFILE_H_*/
