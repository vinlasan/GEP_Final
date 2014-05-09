#include "stdafx.h"
#include "ErrorLogManager.h"

eErrorLogManager eErrorLogManager::m_ErrorManager;

eException::eException(int ErrorNumber, std::string ErrorDesc, std::string SrcFileName, int LineNumber)
{
	m_ErrorNumber = ErrorNumber;
	m_ErrorDesc = ErrorDesc;
    m_SrcFileName = SrcFileName;
    m_LineNumber = LineNumber;

	std::stringstream ErrStr;

	ErrStr << "Error Num: " << m_ErrorNumber << "\nError Desc: " << m_ErrorDesc << "\nSrc File: "
		<< m_SrcFileName << "\nLine Number: " << m_LineNumber << "\n";

	m_ErrText = ErrStr.str();
}

//------------------------------------------------------------------------

const char* eException::what()
{
	return m_ErrText.c_str();
}

//------------------------------------------------------------------------

//cErrorLogManager

//------------------------------------------------------------------------

eErrorLogManager::eErrorLogManager()
{
}

//------------------------------------------------------------------------

eErrorLogManager* eErrorLogManager::GetErrorManager()
{
    return &m_ErrorManager;
}

//------------------------------------------------------------------------

//Opens log file
void eErrorLogManager::create(std::string Filename)
{
    m_LogFile.open(Filename.c_str());
}

//------------------------------------------------------------------------

//Commits information to file and clears text cache
void eErrorLogManager::flush()
{
    m_LogFile << m_LogBuffer.str();
    m_LogFile.flush();
    m_LogBuffer.str("");
}

//------------------------------------------------------------------------

//Close log file
void eErrorLogManager::close()
{
    m_LogFile.close();
}

//------------------------------------------------------------------------

void eErrorLogManager::logException(eException e)
{
    m_LogBuffer << getTimeString() << "\n" << e.what();
    flush();
}

//------------------------------------------------------------------------

//Gets current time as string in the form: hours:mins:secs
std::string eErrorLogManager::getTimeString()
{
    std::stringstream TimeStr;

	struct tm *pTime = new tm();
    time_t ctTime; time(&ctTime);
    localtime_s( pTime, &ctTime );

    TimeStr << std::setw(2) << std::setfill('0') <<pTime->tm_hour << ":";
    TimeStr << std::setw(2) << std::setfill('0') <<pTime->tm_min << ":";
    TimeStr << std::setw(2) << std::setfill('0') <<pTime->tm_sec;

    return TimeStr.str();
}

//------------------------------------------------------------------------