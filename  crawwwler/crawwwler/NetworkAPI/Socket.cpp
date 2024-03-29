#include "Socket.h"

#include "../Http/HttpUtils/HttpRequest.h"
#include "../Http/HttpUtils/HttpResponse.h"

#include <sys/types.h>
#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>

namespace Crawwwler {

///////////////////////////////////////////////////////////////
// Constructors

CSocket::CSocket()
{
}

CSocket::~CSocket()
{
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CSocket::SendRequest(	const std::string ServerName,
							const int PortNumber,
							const CHttpRequest& Request,
							CHttpResponse *pResponse) {
	// Check arguments
	if (!pResponse) return false;

	// Call the private method
	std::string Result;
	bool bResult = Send(ServerName, PortNumber, Request, &Result);

	// Set the return value
	if (!pResponse->SetResponse(Result)) return false;
	// We might not have a content-location header pointing to the resource name, so set it manually here
	if (!pResponse->SetResource(Request.GetResource()));

	return bResult;

}

///////////////////////////////////////////////////////////////
// Private Methods

bool CSocket::Send(const std::string ServerName, const int PortNumber, CHttpRequest Request, std::string* pResult) {
	if (!pResult) return false;

	// This functionality is taken from http://www.linuxhowtos.org/C_C++/socket.htm

	// Create and open the actual socket
	int Sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (Sockfd < 0) return false;

	// Find the target server
	const char *c = ServerName.c_str();
	hostent *pServer = gethostbyname(c);
	if (!pServer) return false;

	// Convert the server address ??? is that comment even correct???
	sockaddr_in ServerAddress;
	bzero((char*) &ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	bcopy((char*)pServer->h_addr, (char*)&ServerAddress.sin_addr.s_addr, pServer->h_length);

	// Delete pServer object which is no longer needed
	//delete pServer;
	//pServer = NULL;

	// Set the remote port
	ServerAddress.sin_port = htons(PortNumber);


	// Make the connection
	if (connect(Sockfd, reinterpret_cast<sockaddr*>(&ServerAddress), sizeof(ServerAddress)) < 0) {
		// Couldn't connect
		return false;
	}

	// Send the request
	char RawRequest[1024];
	sprintf(RawRequest, Request.GetRawRequest().c_str());

	int n = send(Sockfd, RawRequest, strlen(RawRequest), 0);

	if (n < 0) {
		// Couldn't write to the socket
		return false;
	}

	// While we're receiving, keep on appending to the result
	std::string Result;
	int bytes_read = 1; // Default value
	char ReadBuffer[4000];
	while (bytes_read > 0) {
		bzero(ReadBuffer, sizeof(ReadBuffer));
		bytes_read = recv(Sockfd, &ReadBuffer, sizeof(ReadBuffer), 0);
		if (bytes_read > 0) {
			// Append to the result
//			std::cout << Result.c_str() << std::endl;

			Result += ReadBuffer;
			//Result.append(ReadBuffer);
		}
		if (bytes_read == -1) {
			Result = "Error";
			return true;
		}
	}

	// Close the socket
	close(Sockfd);

	// Set the return value
	*pResult = Result;

	// Success!!!!
	return true;
}


}
