// UrlExtractor.h
// Plugin for extracting Urls from an in memory representation of an html file

#ifndef URLEXTRACTOR_H_
#define URLEXTRACTOR_H_

#include "../PluginManager/Plugin.h"
#include "../ServerInfo/ServerInfo.h"

namespace Crawwwler {

class CUrlExtractor {
public:
	CUrlExtractor();
	virtual ~CUrlExtractor();

	// Extract all the urls from this http response and populate pList with them
	bool ExtractFrom(CHttpResponse& File, class CManagedUrlList* pList);

private:

};

}

#endif /*URLEXTRACTOR_H_*/
