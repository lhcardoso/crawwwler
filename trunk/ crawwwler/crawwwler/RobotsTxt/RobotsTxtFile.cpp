#include "RobotsTxtFile.h"
#include "../HttpUtils/HttpResponse.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CRobotsTxtFile::CRobotsTxtFile() {
}

CRobotsTxtFile::~CRobotsTxtFile() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CRobotsTxtFile::Parse(const CHttpResponse& RawFile) {
	// ### Not yet implemented
	return true;
}

bool CRobotsTxtFile::Allows(const class CUrl& Url) {
	// ### Not yet implemented
	return true;
}

///////////////////////////////////////////////////////////////
// Private Methods

}
