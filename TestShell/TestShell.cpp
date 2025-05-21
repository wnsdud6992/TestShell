#include "TestShell.h"
#include "MockDriver.h"
#include "gmock/gmock.h"

using namespace testing;

TestShell::TestShell(IDriver* driver_, std::ostream& output_) : driver(driver_), out(output_) {}

void TestShell::help() {
    out << "\n팀명 : Critical Coders\n";
    out << "제작자 : 최준영, 안지수, 조희성, 이아네스, 손민기, 조효진\n\n";

    out << "특정 명령어에 대한 자세한 내용이 필요하면 HELP <명령어 이름>을 입력하십시오.\n\n";

    out << "기본 명령어:\n";
    out << std::left;
    out << "  " << std::setw(20) << "Write" << "입력받은 주소에 입력받은 값을 저장합니다.\n";
    out << "  " << std::setw(20) << "Read" << "입력받은 주소에 저장되어 있는 값을 읽어옵니다.\n";
    out << "  " << std::setw(20) << "fullwrite" << "관리하고 있는 모든 주소에 입력받은 값을 저장합니다.\n";
    out << "  " << std::setw(20) << "fullread" << "관리하고 있는 모든 주소에 저장되어 있는 값을 읽어옵니다.\n\n";

    out << "테스트 명령어:\n";
    out << "  " << std::setw(30) << "1_FullWriteAndReadCompare"
        << "모든 주소에 입력받은 값을 쓴 뒤 다시 읽어와 비교해본다.\n";
    out << "  " << std::setw(30) << "2_PartialLBAWrite"
        << "특정 주소들에 입력받은 값을 동일하게 쓰고 다시 읽어와 비교해본다.\n";
    out << "  " << std::setw(30) << "3_WriteReadAging"
        << "특정 주소에 랜덤한 값을 쓰고 다시 읽어와 비교해본다.\n";

    out << std::endl;
}

void TestShell::write(unsigned int address, unsigned int data){
    Logger::LogPrint("TestShell", __func__, "Write 시작!!!");
	driver->write(address, data);
}

void TestShell::fullwrite(unsigned int data) {
    for(unsigned int address_index = ADDRESS_RANGE_MIN; address_index <= ADDRESS_RANGE_MAX; address_index++){
        driver->write(address_index, data);
    }
}

unsigned int TestShell::read(unsigned int address) {
    return driver->read(address);
}

std::vector<unsigned int> TestShell::fullread() {
    std::vector<unsigned int> readDataList;
    out << "[Full Read: LBA 0 ~ 99]" << std::endl;

    for (unsigned int lba = 0; lba < 100; ++lba) {
        unsigned int data = driver->read(lba);
        out << "[Read]" << " LBA " << lba << " : " << "0x" << std::setw(8) << std::setfill('0') << std::hex << data << std::endl;
        readDataList.push_back(data);
    }
    return readDataList;
}

bool TestShell::readCompare(unsigned int address, unsigned int value) {
    return read(address) == value;
}

void TestShell::erase(unsigned int address, int size) {
    if (address > ADDRESS_RANGE_MAX) {
        throw CustomException("erase inuput address range over");
    }
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
    runEraseCommand(address, size);
}

void TestShell::runEraseCommand(unsigned int address, int size)
{
    //check over address
    if ((address + size) > ADDRESS_RANGE_MAX)
        size = (ADDRESS_RANGE_MAX - address + 1);
    //check over size
    while (size > MAX_ERASE_SIZE) {
        driver->erase(address, MAX_ERASE_SIZE);
        size -= MAX_ERASE_SIZE;
        address += MAX_ERASE_SIZE;
    }
    if (size > 0)
        driver->erase(address, size);
}

void TestShell::erase_range(unsigned int start_address, unsigned int end_address) {
    if (start_address > end_address)
        std::swap(start_address, end_address);
    int size = (end_address - start_address) + 1;

    runEraseCommand(start_address, size);
}

void TestShell::flush() {
    driver->flush();
}

bool TestShell::Script1() {
    for (int loopCnt = 0; loopCnt < Script1_TotalLoopCount; ++loopCnt) {
        writeFive(loopCnt);
        if (readCompareFive(loopCnt) == false) {
            out << "FAIL " << std::endl;
            return false;
        }
    }
    out << "PASS" << std::endl;
    return true;
}

bool TestShell::Script2() {
    for (int loopCnt = 0; loopCnt < Script2_TotalLoopCount; loopCnt++) {
        unsigned int data = Script2Test_Value + loopCnt;

        for (int idx = 0; idx < 5; ++idx) {
            unsigned int address = Script2_Address[idx];    
            write(address, data);
        }

        for (unsigned int address = 0; address < 5; ++address) {
            unsigned int expectedValue = data;
            if (readCompare({ address }, expectedValue) == false) {
                out << "FAIL " << std::endl;
                return false;
            }
        }
    }
    out << "PASS" << std::endl;
    return true;
}

bool TestShell::Script3(){
    for (int loop = 0; loop < Script3_TotalLoopCount; loop++) {
        srand(RAND_SEED + loop);
        unsigned int randomData = (std::rand() << 16) | std::rand();
        driver->write(ADDRESS_RANGE_MIN, randomData);
        driver->write(ADDRESS_RANGE_MAX, randomData);

        if (!(readCompare(ADDRESS_RANGE_MIN, randomData) && readCompare(ADDRESS_RANGE_MAX, randomData))) {
            out << "FAIL " << std::endl;
            return false;
        }
            
    }
    out << "PASS" << std::endl;
    return true;
}

bool TestShell::Script4() {
    driver->erase(0, 3);
    for (unsigned int loopCnt = 0; loopCnt < Script4_TotalLoopCount; loopCnt++) {
        unsigned int data = Script2Test_Value + loopCnt;
        for (unsigned int base_addr = Script4_StartAddress; base_addr <= Script4_EndAddress; base_addr += 2){
            driver->write(base_addr, data);
            if (!readCompare(base_addr, data)) {
                out << "FAIL " << std::endl;
                return false;
            }
            driver->write(base_addr, data+1);
            if (!readCompare(base_addr, data + 1)) {
                out << "FAIL " << std::endl;
                return false;
            }
            driver->erase(base_addr, 3);
            for (unsigned int erase_addr = 0; erase_addr < 3; ++erase_addr) {
                if (!readCompare(base_addr + erase_addr, 0x00000000)) {
                    out << "FAIL " << std::endl;
                    return false;
                }
            }
        }
    }
    out << "PASS" << std::endl;
    return true;
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
            out << "FAIL";
            return false;
        }
    }
    return true;
}

