#ifndef DOMAINCRAWLERLIST_H_
#define DOMAINCRAWLERLIST_H_

#include "DomainCrawler.h"

namespace Crawwwler {

class CDomainCrawlerList : public std::list<CDomainCrawler> {
public:
	CDomainCrawlerList();
	virtual ~CDomainCrawlerList();
};

}

#endif /*DOMAINCRAWLERLIST_H_*/
