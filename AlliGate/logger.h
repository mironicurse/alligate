#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>

using std::cerr;
using std::string;

#define LOG logger::getInstance().log

const string logLevels[] = {
    "CRITICAL", "ERROR", "WARNING", "INFO", "DEBUG", "EXTENDED"
};
enum logLevel {
    LVL_EXTENDED = 5, LVL_DEBUG = 4, LVL_INFO = 3, LVL_WARNING = 2, LVL_ERROR = 1, LVL_CRITICAL = 0
};

struct loggerSettings
{
    bool useStderr;
    int verboseLevel;

    loggerSettings()
    {
        verboseLevel = 5;
        useStderr = true;
    }
};

class logger;
class loggerDestroyer
{
private:
    logger *p_instance;
public:
    ~loggerDestroyer();

    void init(logger *p);
};

class logger {
    const int MSG_SIZE = 1500;

    static logger *p_instance;
    static loggerDestroyer destroyer;
    friend class loggerDestroyer;

    loggerSettings settings;

    logger(const logger &);
    logger &operator=(logger &);    
public:
    static logger &getInstance();
    logger() {}
    ~logger() {}

    logger &operator()();
    void log(const char *trace, logLevel level, const char *format, ...);
    void setSettings(const loggerSettings &settings)
    {
        this->settings = settings;
    }
};


#endif // LOGGER_H
