#include "TestShell.h"
#include "MockDriver.h"
#include "gmock/gmock.h"

#include <iostream>

using namespace testing;

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}

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

std::pair<std::string, std::vector<unsigned int>> TestShell::parameterParsing(std::string& param) {
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

std::pair<unsigned int, unsigned int > TestShell::CheckWriteParamValid(const std::vector<unsigned int> &command_param) {
    if (command_param.size() != 2) {
        throw CustomException("write command argument error");
    }
    return { command_param[0], command_param[1] };
}

void TestShell::write(unsigned int address, unsigned int data){
    Logger::getInstance().LogPrint("TestShell", __func__, "Write 시작!!!");
	driver->write(address, data);
}

unsigned int TestShell::CheckFullWriteParamValid(const std::vector<unsigned int>& command_param) {
    if (command_param.size() != 1) {
        throw CustomException("write command argument error");
    }
    return command_param[0];
}

void TestShell::fullwrite(unsigned int data) {
    for(int address_index = TestShell::ADDRESS_RANGE_MIN; address_index <= TestShell::ADDRESS_RANGE_MAX; address_index++){
        driver->write(address_index, data);
    }
}

unsigned int TestShell::CheckReadParamValid(const std::vector<unsigned int>& param) {
    if (param.size() != 1)
        throw CustomException("read command argument error");
    if (param[0] < 0 || param[0] > 99)
        throw CustomException("address size error");
    return param[0];
}

unsigned int TestShell::read(unsigned int address) {
    return driver->read(address);
}

std::vector<unsigned int> TestShell::fullread() {
    std::vector<unsigned int> readDataList;
    std::cout << "[Full Read: LBA 0 ~ 99]" << std::endl;

    for (unsigned int lba = 0; lba < 100; ++lba) {
        unsigned int data = driver->read(lba);
        std::cout << "[Read]" << " LBA " << lba << " : " << "0x" << std::setw(8) << std::setfill('0') << std::hex << data << std::endl;
        readDataList.push_back(data);
    }
    return readDataList;
}

bool TestShell::readCompare(unsigned int address, unsigned int value) {
    return read(address) == value;
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

bool TestShell::Script2() {
    for (int loopCnt = 0; loopCnt < Script2_TotalLoopCount; loopCnt++) {
        unsigned int data = Script2Test_Value + loopCnt;

        for (int idx = 0; idx < 5; ++idx) {
            unsigned int address = Script2_Address[idx];    
            writeWithNewParam(address, data);
        }

        for (unsigned int address = 0; address < 5; ++address) {
            unsigned int expectedValue = data;
            if (readCompare({ address }, expectedValue)) {
                std::cout << "PASS" << std::endl;
            }
            else {
                std::cout << "FAIL " << loopCnt;
                return false;
            }
        }
    }
    return true;
}

bool TestShell::Script3(){
    for (int loop = 0; loop < Script3_TotalLoopCount; loop++) {
        srand(RAND_SEED + loop);
        unsigned int randomData = (std::rand() << 16) | std::rand();
        driver->write(TestShell::ADDRESS_RANGE_MIN, randomData);
        driver->write(99, randomData);

        if (!(readCompare(TestShell::ADDRESS_RANGE_MIN, randomData) && readCompare(TestShell::ADDRESS_RANGE_MAX, randomData)))
            return false;
    }
    return true;
}

void TestShell::writeWithNewParam(unsigned int address, unsigned int writevalue){
    write(address, writevalue);
}

unsigned int TestShell::readWithNewParam(unsigned int address) {
    return read(address);
}

void TestShell::writeFive(int loopCnt){
    for (int iter = 0; iter < Script1_OnceLoopCount; iter++) {
        unsigned int address = loopCnt + iter;
        unsigned int expectedValue = ScriptTest_Value + loopCnt;

        write(address, expectedValue);
    }
}

bool TestShell::readCompareFive(int loopCnt) {
    for (int iter = 0; iter < Script1_OnceLoopCount; iter++) {
        unsigned int address = loopCnt + iter;
        unsigned int expectedValue = ScriptTest_Value + loopCnt;
        if (read(address) != expectedValue) {
            std::cout << "FAIL";
            return false;
        }
    }
    return true;
}

