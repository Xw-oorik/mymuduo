#pragma once
#include <string>

#include "noncopyable.h"

// 提供给用户的接口
// LOG_INFO("%s %d", arg1,arg2)

#define LOG_INFO(logmsgFormat, ...)                        \
    do                                                     \
    {                                                      \
        Logger &logger = Logger::getinstance();            \
        logger.setLogLevel(INFO);                          \
        char buff[1024] = {0};                             \
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buff);                                  \
    } while (0)
// do while  防止意想不到的错误
// ##__VA_ARGS__接收可变参的
#define LOG_FATAL(logmsgFormat, ...)                       \
    do                                                     \
    {                                                      \
        Logger &logger = Logger::getinstance();            \
        logger.setLogLevel(FATAL);                         \
        char buff[1024] = {0};                             \
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buff);                                  \
        exit(-1);                                          \
    } while (0)
#define LOG_ERROR(logmsgFormat, ...)                       \
    do                                                     \
    {                                                      \
        Logger &logger = Logger::getinstance();            \
        logger.setLogLevel(ERROR);                         \
        char buff[1024] = {0};                             \
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buff);                                  \
    } while (0)

// debug 默认关闭的 手动开启，要是自动开启的话打印的东西太多了，效率也低
#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat, ...)                        \
    do                                                     \
    {                                                      \
        Logger &logger = Logger::getinstance();            \
        logger.setLogLevel(DEBUG);                          \
        char buff[1024] = {0};                             \
        snprintf(buff, 1024, logmsgFormat, ##__VA_ARGS__); \
        logger.log(buff);                                  \
    } while (0)
#else
    #define LOG_DEBUG(logmsgFormat, ...)
#endif

// 定义日志级别   INFO  ERROR FATAL  DEBUG  DEBUG   TRACE
enum LogLevel
{
    INFO,  // 普通信息
    ERROR, // 错误信息
    FATAL, // core信息 致命错误
    DEBUG, // 调试信息
};

// 输出一个日志类
class Logger : noncopyable
{
public:
    // 获取日志唯一对象
    static Logger &getinstance();
    // 设置日志级别
    void setLogLevel(int level);
    // 写日志
    void log(std::string msg);

private:
    int logLevel_; // 日志级别
};