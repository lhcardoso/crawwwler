// ManagedUrlList.h
// Represents a list of urls that are added to in a unique manner.  This class keeps track of items it has already had
// on its list even if they have been popped, and won't allow them on again
#ifndef MANAGEDURLLIST_H_
#define MANAGEDURLLIST_H_

#include "../HttpUtils/Url.h"
#include <list.h>

namespace Crawwwler {

// Private inheritance so nobody can mess with the list
class CManagedUrlList : private std::list<CUrl> {
public:
	CManagedUrlList();
	virtual ~CManagedUrlList();

	// Add a completely unique url to the list that has never been on the list before at all
	void AddUnique(const CUrl& Url);
	void AddUnique(CManagedUrlList& Rhs);

	// Whether this list is empty
	bool IsEmpty() { return m_CurrentItems.empty(); };

	// Get the next url from the list, the caller is now responsible for the memory
	CUrl* Pop();

	// Expose begin and end so we can access them when uniquely adding a list
	iterator begin() { return this->begin(); };
	iterator end() { return this->end(); };

private:
	// Whether this url has previously existed on this list, but not currently
	bool PreviouslyListed(CUrl Url);
	// Whether this url currently exists on this list
	bool CurrentlyListed(CUrl Url);

	// List of items that were once on the current list
	std::list<CUrl> m_PastItems;
	// The current list of urls
	std::list<CUrl> m_CurrentItems;
};

}

#endif /*MANAGEDURLLIST_H_*/
