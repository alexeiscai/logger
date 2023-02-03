#include "logger.h"
#include <windows.h>
#include <filesystem>

Logger* Logger::getInstance()
{
    if (logger_ == nullptr)
    {
        logger_ = new Logger();
    }
    return logger_;
}

void Logger::log(const std::string &log)
{
   mLogs_.lock();
   logs_.push(log);
   mLogs_.unlock();
}

void Logger::flush()
{
    std::cout<< "Flush "<< logs_.size() << " logs "<< std::endl; 
    while (!logs_.empty())
    {
        logs_.pop();
    }
}

void Logger::writeLogs()
{   
    char filename[MAX_PATH];
    DWORD size = GetModuleFileNameA( NULL, filename, MAX_PATH );
    
    running_ = true;

    while(running_)
    {
        if(logs_.size() > 10)
        {   
            std::cout<< "-------------"<< std::endl;;
            std::cout << filename << " : 10 logs block follows: "<< std::endl;
            std::cout<< "-------------"<< std::endl;
            for(int i = 0; i < 10; i++)
            {
              std::cout<< logs_.front() << std::endl;
              logs_.pop();
            }
            std::cout<< "-------------"<< std::endl;
        }
    }
    flush();
}

void Logger::stop()
{
    mRun_.lock();
    running_ = false;
    mRun_.unlock();
}
