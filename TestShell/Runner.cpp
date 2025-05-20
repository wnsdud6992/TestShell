#include "Runner.h"
#include <iostream>

Runner::Runner(TestShell* shell_) : shell(shell_) {}

void Runner::runFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "���� ���� ����: " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        bool result = handleCommand(line);
        std::cout << "Run...." << (result ? "pass" : "fail") << std::endl;
    }
}

bool Runner::handleCommand(const std::string& command) {
    try {
        if (command == "1_FullWriteAndReadCompare") {
            shell->Script1();
            return true;
        }
        else if (command == "2_PartialLBAWrite") {
            shell->Script2();
            return true;
        }
        else if (command == "3_WriteReadAging") {
            shell->Script3();
            return true;
        }
        //else if (command == "4_EraseAndWriteAging") {
        //    shell.erase
        //}
    }
    catch (...) {
        // ���� �� catch
    }

    return false;
}