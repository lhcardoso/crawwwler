#include "HttpClient.h"

#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/Url.h"
#include "../HttpUtils/Port.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CHttpClient::CHttpClient() {
}

CHttpClient::~CHttpClient() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CHttpClient::GetResource(const CUrl& Url, const CCPort& Port, CHttpResponse *pResponse) const {
	return NULL;
}

///////////////////////////////////////////////////////////////
// Private Methods

}
