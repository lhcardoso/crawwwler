#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <list>
#include "PluginId.h"

namespace GoldDigger
{

class CPlugin
{
public:
	CPlugin();
	virtual ~CPlugin();
	
	// Init the plugin
	virtual bool Init() = 0;
	// Start the plugin
	virtual bool Start() = 0;
	// Stop the plugin
	virtual bool Stop() = 0;
	
	/////////////////////////////////////////////////////////////////
	// Public Methods
	
	// Add another plugin to the list of subscribers
	bool AddSubscriber(CPlugin *pSubscriber);
	// Remove another plugin from the list of subscribers
	bool RemoveSubscriber(const CPluginId& Id);
	
	// As a subscriber, push data into this plugin, this will be overridden by inherited classes,
	// The caller still owns the memory of the data and so it should be copied if needed
	virtual bool PushData(std::list<void*> Data) = 0;
	
private:	
	
	// The id of this plugin
protected:
	// The other plugins that subscribe to the output of this plugin
	std::list<CPlugin*> m_Subscribers;
};

}

#endif /*PLUGIN_H_*/
