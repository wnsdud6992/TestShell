#include "Logger.h"

void Logger::LogPrint(const std::string& className, const std::string& methodName, const std::string& detail) {
    createLogFolder();
    std::string log = formatLogMessage(className, methodName, detail);
    if(!writeToFile(log)) return;
    CheckLogFileToChange();
}

std::string Logger::formatLogMessage(const std::string& className, const std::string& methodName, const std::string& detail) {
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

    return logStream.str();
}

bool Logger::writeToFile(const std::string& text) {
    std::ofstream logFile(LogDir + "\\" + LogFileName, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "로그 파일을 열 수 없습니다." << std::endl;
        return false;
    }
    logFile << text;
    return true;
}

void Logger::CheckLogFileToChange() {
    std::filesystem::path logPath = std::filesystem::path(LogDir) / LogFileName;

    if (std::filesystem::file_size(logPath) >= LogFileMaxSize) {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm localTime;

        localtime_s(&localTime, &t);

        std::ostringstream oss;
        oss << LOG_PREFIX
            << std::put_time(&localTime, "%y%m%d_")
            << localTime.tm_hour << "h_"
            << localTime.tm_min << "m_"
            << localTime.tm_sec << "s"
            << LOG_EXT;


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
    ZipOldestLogFile();
}

void Logger::ZipOldestLogFile() {
    std::vector<std::filesystem::directory_entry> untilLogs;
    for (const auto& entry : std::filesystem::directory_iterator(LogDir)) {
        if (!entry.is_regular_file()) continue;

        std::string filename = entry.path().filename().string();
        if (filename.starts_with(LOG_PREFIX) && filename.ends_with(LOG_EXT)) {
            untilLogs.push_back(entry);
        }
    }

    if (untilLogs.size() >= 2) {
        std::sort(untilLogs.begin(), untilLogs.end(), [](const auto& a, const auto& b) {
            return std::filesystem::last_write_time(a) < std::filesystem::last_write_time(b);
            });

        const auto& oldestFile = untilLogs.front().path();
        std::filesystem::path renamed = oldestFile;
        renamed += ZIP_EXT;

        try {
            std::filesystem::rename(oldestFile, renamed);
        }
        catch (const std::exception& e) {
            std::cerr << "Rename 실패: " << e.what() << '\n';
        }
    }
}

void Logger::createLogFolder() {
    if (!std::filesystem::exists(LogDir)) {
        try {
            std::filesystem::create_directories(LogDir);
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "[Error] Log directory create failed : " << e.what() << '\n';
        }
    }
}