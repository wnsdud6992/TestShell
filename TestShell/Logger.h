#pragma once
#include "Common.h"

constexpr const char* LOG_PREFIX = "until_";
constexpr const char* LOG_EXT = ".log";
constexpr const char* ZIP_EXT = ".zip";

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static void LogPrint(const std::string& className, const std::string& methodName, const std::string& detail);
    
    static std::string formatLogMessage(const std::string& className, const std::string& methodName, const std::string& detail);

    static bool writeToFile(const std::string& text);

    static void CheckLogFileToChange();

    static void ZipOldestLogFile();

    static void createLogFolder();

private:
    Logger() {}   

};