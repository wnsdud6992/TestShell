#include "Runner.h"
#include <iostream>

Runner::Runner(TestShell* shell_) : shell(shell_) {}

void Runner::runFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "파일 열기 실패: " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << " ---  Run....";
        bool result = handleCommand(line);
        std::cout << (result ? "Pass" : "FAIL!") << std::endl;
        if (!result) return;
    }
}

bool Runner::handleCommand(const std::string& command) {
    try {
        if (command == "1_FullWriteAndReadCompare") {
            return shell->Script1();
        }
        else if (command == "2_PartialLBAWrite") {
            return shell->Script2();
        }
        else if (command == "3_WriteReadAging") {
            return shell->Script3();
        }
        else if (command == "4_EraseAndWriteAging") {
            return shell->Script4();
        }
    }
    catch (...) {
    }
    return false;
}