//============================================================================
// Name        : testCrawwwler.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Test project for crawwwler library, currently won't run while design changes are being made
//============================================================================

#include <iostream>
#include "../Utils/LogFile.h"
#include "../DomainCrawler/DomainCrawler.h"
using namespace std;
//using namespace Crawwwler;

int main(int argc, char *argv[]) {
	// ### Most of this code is for testing only.  As the system matures, we'll work on formalising the running and control of the plugins

		// Parse the command line arguments
		int ArgCount = 0;
		while (argv[ArgCount]) {
			std::cout << argv[ArgCount] << std::endl;
			ArgCount++;
		}

		if (ArgCount == 1) {

			std::cout << "Enter a domain name" << std::endl;
			return 0;
		}

		// Get the target server name
		std::string TargetDomainName = argv[1];

		// Crawl the domain
		Crawwwler::CDomainCrawler DomainCrawler(TargetDomainName);
		//if (!DomainCrawler.CrawlUrls()) {
		//	std::cout << "Unsuccessful crawl. Boooo!" << std::endl;
		//	return 0;
		//}
		// Success
		std::cout << "Successful Crawl! yay!" << std::endl;
		Crawwwler::CLogFile Logger;
		Logger.Write("Ok");
		return 0;
}
