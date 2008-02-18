// Plugin.h
// Base class for all plugins

#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <list>
#include "PluginId.h"

namespace Crawwwler {

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

private:

protected:

};

}

#endif /*PLUGIN_H_*/
