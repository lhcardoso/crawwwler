#include "HttpResponseList.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CHttpResponseList::CHttpResponseList() {
}

CHttpResponseList::~CHttpResponseList() {
}

///////////////////////////////////////////////////////////////
// Public Methods

void CHttpResponseList::AddResponses(const CHttpResponseList& Other) {
	// Add each item from the other list
	for (std::list<CHttpResponse>::const_iterator i = Other.begin(); i != Other.end(); i++) {
		AddResponse(*i);
	}
}

///////////////////////////////////////////////////////////////
// Private Methods

}
