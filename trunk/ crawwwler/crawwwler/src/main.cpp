// main.cpp

#include <iostream>
#include "../Crawler/CrawlerPlugin.h"
#include "../HttpUtils/HttpResponse.h"
#include "../HttpUtils/RemoteServer.h"
#include "../UrlExtractor/UrlExtractor.h"
#include "../ServerInfo/ServerInfo.h"
#include "../HttpUtils/Url.h"
#include "../Utils/LogFile.h"

using namespace Crawwwler;

int main() {
	// ### Most of this code is for testing only.  As the system matures, we'll work on formalising the running and control of the plugins


	// Create the crawler object
	CCrawlerPlugin Crawler;

	// Create the url extractor and subscribe it to the crawler plugin's output
	CUrlExtractor Extractor;
	Crawler.AddSubscriber(&Extractor);
	Extractor.AddSubscriber(&Crawler);

	// Add a server
	CRemoteServer *pServer = new CRemoteServer();
	// ### Set this server to point to your local machine or test server in the form "servername.ext"
	if (!pServer->SetServer("morag")) {
		std::cout << "Couldn't set server" << std::endl;
	}
	CServerInfo *pServerInfo = new CServerInfo();
	if (!pServerInfo->SetServer(pServer));

	if (!Crawler.AddServer(pServerInfo)) {
		std::cout << "Couldn't add server" << std::endl;
		return 0;
	}

	// Run a little test which should get all the pages from the site set in the pServer->SetServer() command above
	bool bRunning = true;
	while (bRunning) {
		bRunning = Crawler.Start();
		// The extractor::Start() currently returns false if there's nothing for it to work on
		if (!Extractor.Start()) {
			bRunning = false;
		}

	}

	// Some dummy output to make us feel better

	std::cout << "Crawl Successful" << std::endl;

	// Get the responses
	std::list<CHttpResponse*> Responses;
	Responses = Crawler.CollectResponses();

	std::cout << "Getting Responses" << std::endl;
	if (Responses.size() == 0) {
		std::cout << "No Responses" << std::endl;
		return 0;
	}


	// Output the response
	CHttpResponse *pResponse = Responses.front();
	if (!pResponse) {
		std::cout << "No Response" << std::endl;
		return 0;
	}

	std::cout << "Extracted! yay!" << std::endl;
	CLogFile Logger;
	Logger.Write("Ok");
	return 0;
}
