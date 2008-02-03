#include "Plugin.h"

namespace Crawwwler {

CPlugin::CPlugin() {
}

CPlugin::~CPlugin() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CPlugin::AddSubscriber(CPlugin *pSubscriber) {
	m_Subscribers.push_back(pSubscriber);
	return true;
}

bool CPlugin::RemoveSubscriber(const CPluginId& Id) {
	return false;
}

}
