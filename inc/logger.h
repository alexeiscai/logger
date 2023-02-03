#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>


class Logger
{

private:  

    Logger();
    
    /* Logger object */
    static Logger logger_;

    /* Stoop condition */
    bool running_;
    
    /* Queue of logs in string format */
	std::queue<std::string > logs_;
	
	std::mutex mLogs_;
	std::mutex mRun_;

    /* Flush  logs.*/
    void flush();

public:

/**
 * @brief Get the Instance of Logger class.
 * 
 * @return Logger& addres for current instance.
 */
static Logger &getInstance();

Logger(Logger &other) = delete;

void operator=(const Logger &) = delete;

/**
 * @brief Method push log into queue.
 * 
 * @param msg Log message in a string format.
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