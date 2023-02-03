#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <unistd.h>

class Logger
{
protected:
    Logger(){}
    
    static Logger* logger_;

private:  
  
    bool running;
    std::queue<std::string > logs;
  
    std::mutex m_logs;
    std::mutex m_run;
    
    void flush()
    {
        std::cout<< "Flush queue:"<< logs.size() << " logs "<< std::endl; 
        while (!logs.empty())
        {
            logs.pop();
        }
    }
    
public:

    static Logger* getInstance()
    {   
        if (logger_ == NULL)
        {
            logger_ = new Logger();
        }
        return logger_;
    }
    
    void log(std::string log)
  {
      m_logs.lock();
      logs.push(log);
      m_logs.unlock();
  }
    
    void writeLogs()
  {
        running = true;

          while(running)
          {
            if(logs.size() > 10)
            {
               std::cout<< "-------Block of 10 logs------"<< std::endl;;
                for(int i = 0; i < 10; i++)
                {
                    std::cout<< logs.front() << std::endl;
                    logs.pop();
                }
             std::cout<< "-------------"<< std::endl;;
            }
          }
          flush();
  
  }
  
  void stop()
  {
      m_run.lock();
      running = false;
      m_run.unlock();
  }

};

Logger* Logger ::logger_ = NULL;


int main() {
    Logger* loggerObj = Logger::getInstance();
    
    std::thread thr(&Logger::writeLogs, loggerObj);
    
    for(int i = 0; i < 1000; i++)
    {
        loggerObj->log("LOG--->");
    }
    
    usleep(500);
    loggerObj->stop();
    thr.join();
    
    return 0;
}