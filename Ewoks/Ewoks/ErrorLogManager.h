#ifndef ERRORLOGMANAGER_H_INCLUDED
#define ERRORLOGMANAGER_H_INCLUDED

//------------------------------------------------------------------------

#include "EngineObject.h"
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <exception>

#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(ErrorNum, ErrorDesc) throw cException(ErrorNum, ErrorDesc, __FILE__, __LINE__ );
#endif

//------------------------------------------------------------------------

//Custom exception class

class eException : public std::exception
{
    private:
    protected:
    public:
    int m_ErrorNumber;
    std::string m_ErrorDesc;
    std::string m_SrcFileName;
    int m_LineNumber;
	std::string m_ErrText;

    // Override std::exception::what
    const char* what();

    eException(int ErrorNumber, std::string ErrorDesc, std::string SrcFileName, int LineNumber);
    ~eException() throw() {}
};

//------------------------------------------------------------------------

//Singleton Logging Object

class eErrorLogManager 
{
    public:
        static eErrorLogManager * GetErrorManager();

    protected:
        eErrorLogManager();
        virtual ~eErrorLogManager(){}
        static eErrorLogManager m_ErrorManager;

    public:
        std::stringstream m_LogBuffer;
        void create(std::string Filename);
        void flush();
        void close();
        void logException(eException e);
        std::string getTimeString();
        std::ofstream m_LogFile;
};

//------------------------------------------------------------------------

#endif // ERRORLOGMANAGER_H_INCLUDED
