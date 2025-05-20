#pragma once
#pragma once
#include "TestShell.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Runner {
public:
    Runner(TestShell* shell);
    void runFromFile(const std::string& filepath);

private:
    TestShell* shell;
    bool handleCommand(const std::string& commandLine);
};
