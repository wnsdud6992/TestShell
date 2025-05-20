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

	void LogPrint(const std::string& className, const std::string& methodName, const std::string& detail);

private:
    Logger() {}
};