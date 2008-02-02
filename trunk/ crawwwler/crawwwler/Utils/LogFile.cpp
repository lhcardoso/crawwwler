#include "LogFile.h"

#include <fstream.h>

namespace GoldDigger
{
#define DefaultDiggerLogFile "DLog.txt"
#define DefaultDiggerPath "/home/dave/"
#define DefaultDiggerLogFilePath "/home/dave/DLog.txt"


///////////////////////////////////////////////////////////////
// Constructors

CLogFile::CLogFile() : m_Filename(DefaultDiggerLogFile) {
	
}

CLogFile::CLogFile(std::string Filename) : m_Filename(Filename) {
}

CLogFile::~CLogFile() {
}

///////////////////////////////////////////////////////////////
// Public Methods

bool CLogFile::Write(std::string Message) {
	
	// Build the full path
	std::string LogPath;
	LogPath.append(DefaultDiggerPath);
	LogPath.append(m_Filename);
	
	ofstream Logger(LogPath.c_str());
	
	// Clear the file if this is not the default log file
	std::string NewMessage("");
	if (LogPath == DefaultDiggerLogFilePath) {
		ifstream inFile;
		inFile.open(LogPath.c_str());
		if (inFile) {
			char *pTemp;
			while (inFile >> *pTemp) {
				NewMessage.append(pTemp);
			}
		}
	}
	
	// Write the string	
	NewMessage.append(Message);
	Logger << NewMessage;
	// End the line
	Logger << "\n";

	
	Logger.close();
	
	return true;
}


	
///////////////////////////////////////////////////////////////
// Private Methods
}
