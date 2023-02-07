#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>

class Logger
{

protected:

    Logger() {}

    /* Logger object */
    static Logger *logger_;

private:
    /* Stop condition */
    bool running_;

    /* Queue of logs in string format */
    std::queue<std::string> logs_;

    /* mutex used in log method */
    std::mutex mLogs_;

    /* mutex used in stop method which updates running_ flag */
    std::mutex mRun_;

    /* flush  logs.*/
    void flush();

public:
    /* get instance of Logger class */
    static Logger *getInstance();

    /**
     * @brief Method push log into queue.
     *
     * @param msg Log message of type string.
     */
    void log(const std::string &msg);

    /**
     * @brief Display logs in block of 10.
     *
     */
    void writeLogs();

    /**
     * @brief Set stop condition if logs already displayed.
     *
     */
    void stop();
};

#endif