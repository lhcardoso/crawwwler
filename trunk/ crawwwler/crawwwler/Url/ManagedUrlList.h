// ManagedUrlList.h
// Represents a list of urls that are added to in a unique manner.  This class keeps track of items it has already had
// on its list even if they have been popped, and won't allow them on again
#ifndef MANAGEDURLLIST_H_
#define MANAGEDURLLIST_H_

#include "../HttpUtils/Url.h"

namespace Crawwwler {

class CManagedUrlList
{
public:
	CManagedUrlList();
	virtual ~CManagedUrlList();

	// Add a completely unique url to the list that has never been on the list before at all
	void AddUnique(const class CUrl& Url);
	void AddUnique(const CManagedUrlList& Rhs);

	// Whether this list is empty
	bool IsEmpty() { return false; };

	// Get the next url from the list, the caller is now responsible for the memory
	CUrl* GetNext() { return NULL; };
};

}

#endif /*MANAGEDURLLIST_H_*/
