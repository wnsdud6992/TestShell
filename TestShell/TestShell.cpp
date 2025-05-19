#include "TestShell.h"
#include <iostream>

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}

void TestShell::write(std::vector<unsigned int> command_param){
    if (command_param.size() != 2) {
        throw CustomException("write command argument error");
    }

    const unsigned int address = command_param[0];
    const unsigned int data = command_param[1];
	driver->write(address, data);
}

void TestShell::fullwrite(std::vector<unsigned int> command_param) {
    if (command_param.size() != 1) {
        throw CustomException("write command argument error");
    }

    const unsigned int data = command_param[0];
    for(int address_index = TestShell::ADDRESS_RANGE_MIN; address_index <= TestShell::ADDRESS_RANGE_MAX; address_index++){
        driver->write(address_index, data);
    }
}

void TestShell::help() {
    std::cout << "\n팀명 : Critical Coders\n";
    std::cout << "제작자 : 최준영, 안지수, 조희성, 이아네스, 손민기, 조효진\n\n";

    std::cout << "특정 명령어에 대한 자세한 내용이 필요하면 HELP <명령어 이름>을 입력하십시오.\n\n";

    std::cout << "기본 명령어:\n";
    std::cout << std::left;
    std::cout << "  " << std::setw(20) << "Write" << "입력받은 주소에 입력받은 값을 저장합니다.\n";
    std::cout << "  " << std::setw(20) << "Read" << "입력받은 주소에 저장되어 있는 값을 읽어옵니다.\n";
    std::cout << "  " << std::setw(20) << "fullwrite" << "관리하고 있는 모든 주소에 입력받은 값을 저장합니다.\n";
    std::cout << "  " << std::setw(20) << "fullread" << "관리하고 있는 모든 주소에 저장되어 있는 값을 읽어옵니다.\n\n";

    std::cout << "테스트 명령어:\n";
    std::cout << "  " << std::setw(30) << "1_FullWriteAndReadCompare"
        << "모든 주소에 입력받은 값을 쓴 뒤 다시 읽어와 비교해본다.\n";
    std::cout << "  " << std::setw(30) << "2_PartialLBAWrite"
        << "특정 주소들에 입력받은 값을 동일하게 쓰고 다시 읽어와 비교해본다.\n";
    std::cout << "  " << std::setw(30) << "3_WriteReadAging"
        << "특정 주소에 랜덤한 값을 쓰고 다시 읽어와 비교해본다.\n";

    std::cout << std::endl;
}

std::pair<std::string, std::vector<unsigned int>> TestShell::parameterParsing(std::string & param) {
    std::vector<unsigned int> parameter;
    std::string command;
    std::istringstream iss(param);

    if (iss >> command) {
        std::string token;
        while (iss >> token) {
            parameter.push_back(std::stoul(token, nullptr, 0));
        }
    }
    if (std::find(validCommands.begin(), validCommands.end(), command) == validCommands.end()) {
        throw CustomException("INVALID COMMAND");
    }
    return { command, parameter };
}

unsigned int TestShell::read(std::vector<unsigned int> address) {
    if (address.size() != 1)
        std::cerr << "INVALID COMMAND \n";
    if (address[0] < 0 || address[0] > 99)
        std::cerr << "INVALID COMMAND \n";

    return driver->read(address[0]);
}

std::vector<unsigned int> TestShell::fullread() {
    std::vector<unsigned int> readDataList;
    std::cout << "[Full Read: LBA 0 ~ 99]" << std::endl;

    for (unsigned int lba = 0; lba < 100; ++lba) {
        readDataList.push_back(driver->read(lba));
        std::cout << "LBA " << lba << " : 0x"
            << std::hex << readDataList[lba] << std::dec << " (" << readDataList[lba] << ")\n";
    }
    return readDataList;
}

bool TestShell::readCompare(std::vector<unsigned int >address, unsigned int value) {
    int readData = read(address);
    return readData == value;
}

void TestShell::Script1() {
    for (int loopCnt = 0; loopCnt < Script1_TotalLoopCount; ++loopCnt) {
        writeFive(loopCnt);
        if (readCompareFive(loopCnt) == false) {
            return;
        }
    }
    std::cout << "PASS" << std::endl;
}

void TestShell::writeFive(int loopCnt){
    for (int iter = 0; iter < Script1_OnceLoopCount; ++iter) {
        unsigned int address = loopCnt * iter;
        unsigned int expectedValue = ScriptTest_Value + loopCnt;

        std::vector<unsigned int> command_param;
        command_param.push_back(address);
        command_param.push_back(expectedValue);
        write(command_param);
    }
}

bool TestShell::readCompareFive(int loopCnt) {
    for (int iter = 0; iter < Script1_OnceLoopCount; ++iter) {
        unsigned int address = loopCnt * iter;
        unsigned int expectedValue = ScriptTest_Value + loopCnt;

        std::vector<unsigned int> readAddress{ address };
        unsigned int actualValue = read(readAddress);
        if (actualValue != expectedValue) {
            std::cout << "FAIL";
            return false;
        }
    }
    return true;
}

bool TestShell::Script3(){
    int loop = 200;
    while (loop--) {
        srand(RAND_SEED);
        unsigned int random_number = (std::rand() << 16) | std::rand();
        driver->write(0, random_number);
        driver->write(99, random_number);

        std::vector<unsigned int> fistLBA{ 0 };
        std::vector<unsigned int> lastLBA{ 99 };

        if (!(readCompare(fistLBA, random_number) && readCompare(lastLBA, random_number)))
            return false;
    }
    return true;
}
