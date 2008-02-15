// ServerManager.h
// Manages the crawling of a remote server

#ifndef SERVERMANAGER_H_
#define SERVERMANAGER_H_

namespace Crawwwler
{

class CServerManager
{
public:
	CServerManager();
	virtual ~CServerManager();



private:
	CServerManager(const CServerManager& Other);
	CServerManer& operator=(const CServerManager& Rhs);
};

}

#endif /*SERVERMANAGER_H_*/
