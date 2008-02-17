#include "UrlExtractor.h"
#include "../Http/HttpUtils/HttpResponse.h"
#include "../Url/Url.h"
#include "../Url/ManagedUrlList.h"


namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CUrlExtractor::CUrlExtractor()
{
}

CUrlExtractor::~CUrlExtractor()
{
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CUrlExtractor::ExtractFrom(CHttpResponse& File, CManagedUrlList* pList) {
	// Parse the raw response
	if (!File.Parse()) {
		// Ignore this one??
		// ### Can't really do this, though it could mean there is no raw response!!!
		return false;
	}

	// Add all unique urls (not in-page duplicates) exposed by this response
	std::list<CUrl> Urls = File.GetUrls();
	for (std::list<CUrl>::iterator i = Urls.begin(); i != Urls.end(); i++) {
		pList->AddUnique(*i);
	}

	return true;
}

///////////////////////////////////////////////////////////////
// Private Methods

}
