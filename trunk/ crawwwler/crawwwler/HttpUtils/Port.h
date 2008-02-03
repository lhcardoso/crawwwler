// Port.h
// Represents a network interface port

#ifndef PORT_H_
#define PORT_H_

namespace Crawwwler {

// Stupid class name is because ide didn't want to let me call it CPort for some reason!
class CCPort {
public:
	CCPort(int PortNum);
	virtual ~CCPort();
	
	// Get the port number
	int GetPortNum() { return m_PortNum; };
	
private:
	// The port number
	int m_PortNum;
};

}

#endif /*PORT_H_*/
