#pragma once
#include "Common.h"
#include "TestShell.h"

class TestShellCommandFactory {
public:
    TestShellCommandFactory(std::unique_ptr<TestShell>& _testShell) {
        testShell = std::move(_testShell);
    }

    void executeCommand(const std::string & userInput) {
        auto [command_, parameter_] = testShell->commandParsing(userInput);
        command = command_;
        if (command == "erase") {
            eraseParam = testShell->EraseParamParsing(parameter_);
        }
        else {
            parameter = testShell->normalParamParsing(parameter_);
        }
        

        if (commandMap.contains(command)) {
            commandMap[command]();
        }
        else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }
private:
    std::unique_ptr<TestShell> testShell;
    std::vector<unsigned int> parameter;
    std::string command;
    std::pair<unsigned int, int> eraseParam;


    std::unordered_map<std::string, std::function<void()>> commandMap = {
        {"write", [&]() {
            auto [address, data] = testShell->CheckWriteParamValid(parameter);
            testShell->write(address, data);
        }},
        {"read", [&]() {
            unsigned int address = testShell->CheckReadParamValid(parameter);
            testShell->read(address);
        }},
        {"help", [&]() {
            testShell->help();
        }},
        {"fullwrite", [&]() {
            unsigned int data = testShell->CheckFullWriteParamValid(parameter);
            testShell->fullwrite(data);
        }},
        {"fullread", [&]() {
            testShell->fullread();
        }},
        {"1_FullWriteAndReadCompare", [&]() {
            testShell->Script1();
        }},
        {"1_", [&]() {
            testShell->Script1();
        }},
        {"2_PartialLBAWrite", [&]() {
            testShell->Script2();
        }},
        {"2_", [&]() {
            testShell->Script2();
        }},
        {"3_WriteReadAging", [&]() {
            testShell->Script3();
        }},
        {"3_", [&]() {
            testShell->Script3();
        }},
        {"4_EraseAndWriteAging", [&]() {
            testShell->Script4();
        }},
        {"4_", [&]() {
            testShell->Script4();
        }},
        {"exit", [&]() {
            std::cout << "Thank you and bye~" << std::endl;
            exit(0);
    }},
    };
};