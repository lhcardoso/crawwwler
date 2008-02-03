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
	
	bool Write(std::string Message);
	
private:	
	std::string m_Filename;
};

}

#endif /*LOGFILE_H_*/
