#include "TestShell.h"
#include "MockDriver.h"
#include "gmock/gmock.h"

#include <iostream>
#include <algorithm>

using namespace testing;

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}

void TestShell::help() {
    std::cout << "\n���� : Critical Coders\n";
    std::cout << "������ : ���ؿ�, ������, ����, �̾Ƴ׽�, �չα�, ��ȿ��\n\n";

    std::cout << "Ư�� ��ɾ ���� �ڼ��� ������ �ʿ��ϸ� HELP <��ɾ� �̸�>�� �Է��Ͻʽÿ�.\n\n";

    std::cout << "�⺻ ��ɾ�:\n";
    std::cout << std::left;
    std::cout << "  " << std::setw(20) << "Write" << "�Է¹��� �ּҿ� �Է¹��� ���� �����մϴ�.\n";
    std::cout << "  " << std::setw(20) << "Read" << "�Է¹��� �ּҿ� ����Ǿ� �ִ� ���� �о�ɴϴ�.\n";
    std::cout << "  " << std::setw(20) << "fullwrite" << "�����ϰ� �ִ� ��� �ּҿ� �Է¹��� ���� �����մϴ�.\n";
    std::cout << "  " << std::setw(20) << "fullread" << "�����ϰ� �ִ� ��� �ּҿ� ����Ǿ� �ִ� ���� �о�ɴϴ�.\n\n";

    std::cout << "�׽�Ʈ ��ɾ�:\n";
    std::cout << "  " << std::setw(30) << "1_FullWriteAndReadCompare"
        << "��� �ּҿ� �Է¹��� ���� �� �� �ٽ� �о�� ���غ���.\n";
    std::cout << "  " << std::setw(30) << "2_PartialLBAWrite"
        << "Ư�� �ּҵ鿡 �Է¹��� ���� �����ϰ� ���� �ٽ� �о�� ���غ���.\n";
    std::cout << "  " << std::setw(30) << "3_WriteReadAging"
        << "Ư�� �ּҿ� ������ ���� ���� �ٽ� �о�� ���غ���.\n";

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
    Logger::LogPrint("TestShell", __func__, "Write ����!!!");
	driver->write(address, data);
}

unsigned int TestShell::CheckFullWriteParamValid(const std::vector<unsigned int>& command_param) {
    if (command_param.size() != 1) {
        throw CustomException("write command argument error");
    }
    return command_param[0];
}

void TestShell::fullwrite(unsigned int data) {
    for(unsigned int address_index = TestShell::ADDRESS_RANGE_MIN; address_index <= TestShell::ADDRESS_RANGE_MAX; address_index++){
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

void TestShell::erase(unsigned int address, int size) {
    //check minus size
    if (size < 0) {
        int calcAddress = (address + size + 1);
        size *= (-1);
        //check under address
        if (calcAddress < 0) {
            size = (calcAddress + size);
            calcAddress = 0;
        }
        address = calcAddress;
    }
    
    //check over address
    if ((address + size) > ADDRESS_RANGE_MAX)
        size = (ADDRESS_RANGE_MAX - address + 1);
    
    //check over size
    const int MAX_ERASE_SIZE = 10;
    while (size > MAX_ERASE_SIZE) {
        driver->erase(address, MAX_ERASE_SIZE);
        size -= MAX_ERASE_SIZE;
        address += MAX_ERASE_SIZE;
    }
    if (size > 0)
        driver->erase(address, size);
}

void TestShell::erase_range(unsigned int start_address, unsigned int end_size) {
    if (start_address > end_size)
        std::swap(start_address, end_size);
    int size = (end_size - start_address) + 1;
    driver->erase(start_address, size);
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

