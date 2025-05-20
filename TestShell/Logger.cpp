#include "Logger.h"

void Logger::LogPrint(const std::string& className, const std::string& methodName, const std::string& detail) {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};
    localtime_s(&localTime, &nowTime);

    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "[%y.%m.%d %H:%M]");

    // 2. 클래스.메서드 형식 문자열 만들기
    std::ostringstream nameStream;
    nameStream << className << "." << methodName << "( )";

    std::ostringstream logStream;
    logStream << timeStream.str() << " " << std::left << std::setw(30) << nameStream.str() << detail << "\n";

    // 4. 파일에 로그 작성
    std::ofstream logFile(LogFileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << logStream.str();
    }
    else {
        std::cerr << " 로그 파일을 열 수 없습니다." << std::endl;
    }
}