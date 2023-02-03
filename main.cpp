#include "logger.h"
#include <unistd.h>

void displayLogs()
{
    std::thread thr(&Logger::writeLogs, &Logger::getInstance());

     for(int i = 0; i < 100; i++)
    {
        Logger::getInstance().log("Test log---->");
    }
    
    usleep(1000);
    Logger::getInstance().stop();
    thr.join();
}

int main()
{
    displayLogs();

    return 0;
}