// LogFile.h
// Represents a log file on disk
#ifndef LOGFILE_H_
#define LOGFILE_H_

#include <string>

namespace Crawwwler {



class CLogFile {
	
public:
	CLogFile();
	CLogFile(std::string Filename);
	virtual ~CLogFile();
	
	// Write a string to the log file on disk
	bool Write(std::string Message);
	
private:	
	// Path to the log file
	// ### Currently set internally in this class.  Need to be set in an external (xml?) file
	std::string m_Filename;
};

}

#endif /*LOGFILE_H_*/
