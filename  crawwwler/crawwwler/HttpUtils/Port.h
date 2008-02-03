// Port.h
// Represents a network interface port
// Stupid class name is because ide didn't want to let me call it CPort

#ifndef PORT_H_
#define PORT_H_

namespace Crawwwler {

class CCPort {
public:
	CCPort(int PortNum);
	virtual ~CCPort();
	
	int GetPortNum() { return m_PortNum; };
	
private:
	int m_PortNum;
};

}

#endif /*PORT_H_*/
