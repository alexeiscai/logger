#include "logger.h"
#include <unistd.h>

Logger* Logger ::logger_ = NULL;


int main()
{   
    Logger* loggerObj = Logger::getInstance();

    std::thread thr(&Logger::writeLogs, loggerObj);

    for(int i = 0; i < 1000; i++)
    {
        loggerObj->log("Test log---->");
    }
    
    usleep(500);
    loggerObj->stop();
    thr.join();

    return 0;
}