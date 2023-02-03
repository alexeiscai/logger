#include "logger.h"
#include <windows.h>
#include <filesystem>

Logger Logger::logger_ = Logger();

Logger::Logger() {
};

Logger &Logger::getInstance()
{
    return logger_;
}

void Logger::log(const std::string &log)
{
    Logger::getInstance().mLogs_.lock();
    Logger::getInstance().logs_.push(log);
    Logger::getInstance().mLogs_.unlock();
}

void Logger::flush()
{
    std::cout<< "Flush "<< logs_.size() << " logs "<< std::endl; 
    while (!Logger::getInstance().logs_.empty())
    {
        Logger::getInstance().logs_.pop();
    }
}

void Logger::writeLogs()
{   
    char filename[MAX_PATH];
    DWORD size = GetModuleFileNameA( NULL, filename, MAX_PATH );
    
    Logger::getInstance().running_ = true;

    while(Logger::getInstance().running_)
    {
        if(Logger::getInstance().logs_.size() > 10)
        {   
            std::cout<< "-------------"<< std::endl;;
            std::cout << filename << " : 10 logs block follows: "<< std::endl;
            std::cout<< "-------------"<< std::endl;
            for(int i = 0; i < 10; i++)
            {
            std::cout<< Logger::getInstance().logs_.front() << std::endl;
            Logger::getInstance().logs_.pop();
            }
            std::cout<< "-------------"<< std::endl;
        }
    }
    flush();
}

void Logger::stop()
{
    Logger::getInstance().mRun_.lock();
    Logger::getInstance().running_ = false;
    Logger::getInstance().mRun_.unlock();
}
