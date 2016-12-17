#include "logger.h"

logger *logger::p_instance = 0;

loggerDestroyer logger::destroyer;

loggerDestroyer::~loggerDestroyer()
{
    delete p_instance;
}

void loggerDestroyer::init(logger *p)
{
    p_instance = p;
}

logger &logger::getInstance()
{
    if (!p_instance) {
        p_instance = new logger();
        destroyer.init(p_instance);
    }
    return *p_instance;
}

void logger::log(const char *trace, logLevel level, const char *format, ...)
{
    if (level > settings.verboseLevel)
    {
        return;
    }

    char message[MSG_SIZE] = "";
    memset(message, 0, MSG_SIZE);
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(message, sizeof(message), format, argptr);
    va_end(argptr);

    time_t t = time(NULL);
    char *s = ctime(&t);
    s[strlen(s) - 1] = 0;

    /*
    if (settings.sysLog)
    {
        openlog(service_name, LOG_PID | LOG_CONS | LOG_NOWAIT | LOG_NDELAY, 0);
        syslog(LOG_INFO, message, "");
        closelog();
    }
    if (settings.ownLog)
    {
        FILE *f = fopen(settings.logFile.c_str(), "a");
        if (f) {
            fprintf(f, "%s %s %s %s[%d]: %s\n", s,
                    logLevels[level].c_str(), service_name, trace, getpid(), message);
            fclose(f);
        }
    }
    */

    if (settings.useStderr) {
        cerr << s << " " << logLevels[level] << " " << trace
             << "[" << getpid() << "]: " << message << "\n";
    }


    va_end(argptr);

}

logger &logger::operator()()
{
    return logger::getInstance();
}
