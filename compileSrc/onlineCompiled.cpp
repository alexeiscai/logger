#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <unistd.h>

class Logger
{
protected:
    Logger() {}

    /* Logger object */
    static Logger *logger_;

private:
    /* Stop condition */
    bool running;

    /* Queue of logs in string format */
    std::queue<std::string> logs;

    /* mutex used in log method */
    std::mutex mLogs_;

    /* mutex used in stop method which updates running_ flag */
    std::mutex mRun_;

    /**
     * @brief Flush  logs.
     *
     */
    void flush()
    {
        std::cout << "Flush queue:" << logs.size() << " logs " << std::endl;
        while (!logs.empty())
        {
            logs.pop();
        }
    }

public:
    /**
     * @brief Get the Instance object
     *
     * @return Logger object.
     */
    static Logger *getInstance()
    {
        if (logger_ == NULL)
        {
            logger_ = new Logger();
        }
        return logger_;
    }

    /**
     * @brief Method push logs into queue.
     *
     * @param log Log message of type string.
     */
    void log(std::string log)
    {
        mLogs_.lock();
        logs.push(log);
        mLogs_.unlock();
    }

    /**
     * @brief Display logs in block of 10.
     *
     */
    void writeLogs()
    {
        running = true;

        while (running)
        {
            if (logs.size() > 10)
            {
                std::cout << "-------Block of 10 logs------" << std::endl;
                ;
                for (int i = 0; i < 10; i++)
                {
                    std::cout << logs.front() << std::endl;
                    logs.pop();
                }
                std::cout << "-------------" << std::endl;
                ;
            }
        }
        flush();
    }

    /**
     * @brief Set stop condition if logs already displayed.
     *
     */
    void stop()
    {
        mRun_.lock();
        running = false;
        mRun_.unlock();
    }
};

Logger *Logger::logger_ = NULL;

int main()
{
    Logger *loggerObj = Logger::getInstance();

    std::thread thr(&Logger::writeLogs, loggerObj);

    for (int i = 0; i < 1000; i++)
    {
        loggerObj->log("LOG--->");
    }

    usleep(500);
    loggerObj->stop();
    thr.join();

    return 0;
}