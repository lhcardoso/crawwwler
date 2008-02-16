#include "ManagedUrlList.h"

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CManagedUrlList::CManagedUrlList() {
}

CManagedUrlList::~CManagedUrlList() {
}

///////////////////////////////////////////////////////////////
// Public Methods

void CManagedUrlList::AddUnique(const CUrl& Url) {
	// Nothing to do if we currently have or have had this item before
	if (CurrentlyListed(Url)) return;
	if (PreviouslyListed(Url)) return;

	// It's unique, add to the current list
	this->push_back(Url);
}

void CManagedUrlList::AddUnique(CManagedUrlList& Rhs) {

	// Try to add each item uniquely
	for (std::list<CUrl>::iterator i = Rhs.begin(); i != Rhs.end(); i++) {
		CUrl Current(*i);
		// Call the method for single add
		AddUnique(Current);
	}
}
///////////////////////////////////////////////////////////////
// Private Methods

bool CManagedUrlList::PreviouslyListed(CUrl Url) {
	// If the url is in the list of visited resources, then we've been there
	for (std::list<CUrl>::iterator i = m_PastItems.begin(); i != m_PastItems.end(); i++) {
		CUrl Current = *i;
		// ### This will have to be more specific to match the server too
		if (Current.GetResource() == Url.GetResource()) {
			// Already been there
			return true;
		}
	}
	// Couldn't find it
	return false;
}

bool CManagedUrlList::CurrentlyListed(CUrl Url) {
	// If the url is in the list of urls to visit, then we already know about it
	for (std::list<CUrl>::iterator j = this->begin(); j != this->end(); j++) {
		CUrl Current = *j;
		// ### This will have to be more specific to match the server too
		if (Url.GetResource() == Current.GetResource()) return true;
	}

	// Didn't find it in the list
	return false;
}

}
