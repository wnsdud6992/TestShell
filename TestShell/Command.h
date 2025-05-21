#pragma once
#include "Common.h"
#include "TestShell.h"

class ICommand {
public:
    virtual void execute(TestShell& testshell) = 0;
    virtual ~ICommand() = default;
};

class HelpCommand : public ICommand {
public:
    HelpCommand(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("Help command no need argument!\n");        
    }

    void execute(TestShell& testshell) override {
        testshell.help();
    }
};

class ReadCommand : public ICommand {
public:
    ReadCommand(const std::string& args) {
        std::vector<unsigned int> parameter;
        std::istringstream iss(args);
        std::string token;
        while (iss >> token) {
            parameter.push_back(std::stoul(token, nullptr, 0));
        }
        if (parameter.size() != 1)
            throw CustomException("read command argument error\n");
        if (parameter[0] < 0 || parameter[0] > 99)
            throw CustomException("address size error\n");
        address = parameter[0];
    }

    void execute(TestShell& testshell) override {
        testshell.read(address);
    }
private:
    unsigned int address;
};

class FullReadCommand : public ICommand {
public:
    FullReadCommand(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("Full Read command no need argument!\n");
    }
    void execute(TestShell& testshell) override {
        testshell.fullread();
    }
};

class WriteCommand : public ICommand {
public:
    WriteCommand(const std::string& args) {
        std::vector<unsigned int> parameter;
        std::istringstream iss(args);
        std::string token;
        while (iss >> token) {
            parameter.push_back(std::stoul(token, nullptr, 0));
        }
        if (parameter.size() != 2) {
            throw CustomException("write command argument error\n");
        }
        address = parameter[0];
        data = parameter[1];
    }

    void execute(TestShell& testshell) override {
        testshell.write(address, data);
    }

private:
    unsigned int address;
    unsigned int data;
};

class FullWriteCommand : public ICommand {
public:
    FullWriteCommand(const std::string& args) {
        std::vector<unsigned int> parameter;
        std::istringstream iss(args);
        std::string token;
        while (iss >> token) {
            parameter.push_back(std::stoul(token, nullptr, 0));
        }
        if (parameter.size() != 1) {
            throw CustomException("Fullwrite command argument error\n");
        }
        data = parameter[0];
    }

    void execute(TestShell& testshell) override {
        testshell.read(data);
    }
private:
    unsigned int data;
};

class EraseCommand : public ICommand {
public:
    EraseCommand(const std::string& args) {
        std::istringstream iss(args);
        std::string param;
        std::vector<std::string> paramList;

        while (iss >> param) {
            paramList.push_back(param);
        }

        if (paramList.size() >= 3) {
            throw CustomException("Error: Too many parameters! Only two allowed.\n");
        }
        address = std::stoul(paramList[0], nullptr, 0);
        size = std::stoi(paramList[1]);
    }

    void execute(TestShell& testshell) override {
        testshell.erase(address, size);
    }
private:
    unsigned int address;
    int size;
};

class EraseRangeCommand : public ICommand {
public:
    EraseRangeCommand(const std::string& args) {
        std::vector<unsigned int> parameter;
        std::istringstream iss(args);
        std::string token;
        while (iss >> token) {
            parameter.push_back(std::stoul(token, nullptr, 0));
        }
        if (parameter.size() != 2) {
            throw CustomException("erase_range command argument error\n");
        }
        start_address = parameter[0];
        end_address = parameter[1];
    }

    void execute(TestShell& testshell) override {
        testshell.erase_range(start_address, end_address);
    }

private:
    unsigned int start_address;
    unsigned int end_address;
};

class FlushCommand : public ICommand {
public:
    FlushCommand(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("flush command no need argument!\n");
    }

    void execute(TestShell& testshell) override {
        testshell.flush();
    }
};

class Script1Command : public ICommand {
public:
    Script1Command(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("Script1 command no need argument!\n");
    }

    void execute(TestShell& testshell) override {
        testshell.Script1();
    }
};

class Script2Command : public ICommand {
public:
    Script2Command(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("Script2 command no need argument!\n");
    }

    void execute(TestShell& testshell) override {
        testshell.Script2();
    }
};

class Script3Command : public ICommand {
public:
    Script3Command(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("Script3 command no need argument!\n");
    }

    void execute(TestShell& testshell) override {
        testshell.Script3();
    }
};

class Script4Command : public ICommand {
public:
    Script4Command(const std::string& args) {
        if (args.size() != 0)
            throw CustomException("Script4 command no need argument!\n");
    }

    void execute(TestShell& testshell) override {
        testshell.Script4();
    }
};
