// HttpResponseList.h
// Wrapper for a list of CHttpResponse objects

#ifndef HTTPRESPONSELIST_H_
#define HTTPRESPONSELIST_H_

#include "HttpResponse.h"

namespace Crawwwler {

class CHttpResponseList : public std::list<CHttpResponse> {
public:
	CHttpResponseList();
	virtual ~CHttpResponseList();

	void AddResponse(const CHttpResponse& Response) { push_back(Response); };
	void AddResponses(const CHttpResponseList& Other);

private:
	CHttpResponseList(const CHttpResponseList& Other);
	CHttpResponseList& operator=(const CHttpResponseList& Rhs);
};

}

#endif /*HTTPRESPONSELIST_H_*/
