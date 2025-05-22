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
        if (command == "1_FullWriteAndReadCompare" || command == "1_") {
            return shell->Script1();
        }
        else if (command == "2_PartialLBAWrite" || command == "2_") {
            return shell->Script2();
        }
        else if (command == "3_WriteReadAging" || command == "3_") {
            return shell->Script3();
        }
        else if (command == "4_EraseAndWriteAging" || command == "4_") {
            return shell->Script4();
        }
        else {
            std::cout << "run time error (invaild script) : " << command << std::endl;
        }
    }
    catch (...) {
    }
    return false;
}