// HttpResponseList.h
// Wrapper for a list of CHttpResponse objects

#ifndef HTTPRESPONSELIST_H_
#define HTTPRESPONSELIST_H_

#include "HttpResponse.h"

namespace Crawwwler {

class CHttpResponseList : std::list<CHttpResponse> {
public:
	CHttpResponseList();
	virtual ~CHttpResponseList();
};

}

#endif /*HTTPRESPONSELIST_H_*/
