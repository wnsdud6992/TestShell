#pragma once
#include "Common.h"
#include "Command.h"


class CommandFactory {
public:
    CommandFactory() {
        CommandMap["help"] = [](const std::string& args) {
            return std::make_unique<HelpCommand>(args);
            };
        CommandMap["read"] = [](const std::string& args) {
            return std::make_unique<ReadCommand>(args);
            };
        CommandMap["fullread"] = [](const std::string& args) {
            return std::make_unique<FullReadCommand>(args);
            };
        CommandMap["write"] = [](const std::string& args) {
            return std::make_unique<WriteCommand>(args);
            };
        CommandMap["fullwrite"] = [](const std::string& args) {
            return std::make_unique<FullWriteCommand>(args);
            };
        CommandMap["erase"] = [](const std::string& args) {
            return std::make_unique<EraseCommand>(args);
            };
        CommandMap["erase_range"] = [](const std::string& args) {
            return std::make_unique<EraseRangeCommand>(args);
            };
        CommandMap["flush"] = [](const std::string& args) {
            return std::make_unique<FlushCommand>(args);
            };
        CommandMap["Script1"] = [](const std::string& args) {
            return std::make_unique<Script1Command>(args);
            };
        CommandMap["Script2"] = [](const std::string& args) {
            return std::make_unique<Script2Command>(args);
            };
        CommandMap["Script3"] = [](const std::string& args) {
            return std::make_unique<Script3Command>(args);
            };
        CommandMap["Script4"] = [](const std::string& args) {
            return std::make_unique<Script4Command>(args);
            };
    }

    std::unique_ptr<ICommand> parse(const std::string& input) {
        std::istringstream iss(input);
        std::string cmd;
        std::string parameter;
        iss >> cmd;
        std::getline(iss, parameter);

        auto iter = CommandMap.find(cmd);
        if (iter == CommandMap.end()) {
            throw CustomException("INVALID COMMAND\n");
        }

        return iter->second(parameter);
    }
private:
    std::map<std::string, std::function<std::unique_ptr<ICommand>(const std::string&)>> CommandMap;
};