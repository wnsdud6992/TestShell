#pragma once
#include "Common.h"

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static void LogPrint(const std::string& className, const std::string& methodName, const std::string& detail);

    static void CheckLogFileToChange();

private:
    Logger() {}
    
};