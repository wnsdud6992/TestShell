#include "Logger.h"

void Logger::LogPrint(const std::string& className, const std::string& methodName, const std::string& detail) {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};
    localtime_s(&localTime, &nowTime);

    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "[%y.%m.%d %H:%M]");

    std::ostringstream nameStream;
    nameStream << className << "." << methodName << "( )";

    std::ostringstream logStream;
    logStream << timeStream.str() << " " << std::left << std::setw(30) << nameStream.str() << detail << "\n";

    {
        std::ofstream logFile(LogDir + "\\" + LogFileName, std::ios::app);
        if (logFile.is_open()) {
            logFile << logStream.str();
        }
        else {
            std::cerr << "로그 파일을 열 수 없습니다." << std::endl;
            return;
        }
    }
    CheckLogFileToChange();
}

void Logger::CheckLogFileToChange() {
    std::filesystem::path logPath = std::filesystem::path(LogDir) / LogFileName;

    if (std::filesystem::file_size(logPath) >= LogFileMaxSize) {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;

        localtime_s(&localTime, &t);

        std::ostringstream oss;
        oss << "until_"
            << std::put_time(&localTime, "%y%m%d_")
            << localTime.tm_hour << "h_"
            << localTime.tm_min << "m_"
            << localTime.tm_sec << "s"
            << ".log";


        std::filesystem::path newLogPath = std::filesystem::path(LogDir) / oss.str();

        try {
            std::filesystem::rename(logPath, newLogPath);
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "[파일 이동 실패]\n";
            std::cerr << "원인: " << e.what() << '\n';
            std::cerr << "오류 코드: " << e.code() << '\n';
        }
    }
}