#include "TestShell.h"
#include "MockDriver.h"
#include "gmock/gmock.h"

using namespace testing;

TestShell::TestShell(std::unique_ptr<IDriver> driver_, std::ostream& output_) : driver{std::move(driver_)}, out(output_) {}

void TestShell::help() {
    out << "\n팀명 : Critical Coders\n";
    out << "제작자 : 최준영, 안지수, 조희성, 이아네스, 손민기, 조효진\n\n";

    out << "기본 명령어:\n";
    out << std::left;
    out << "  " << std::setw(30) << "write [LBA] [DATA]" << "입력받은 LBA에 입력받은 DATA을 저장합니다.\n";
    out << "  " << std::setw(30) << "read [LBA]" << "입력받은 LBA에 저장되어 있는 값을 읽어옵니다.\n";
    out << "  " << std::setw(30) << "erase [LBA] [SIZE]" << "입력받은 LBA부터 SIZE 개수의 LBA까지 DATA를 삭제합니다.\n";
    out << "  " << std::setw(30) << "erase_range [LBA_1] [LBA_2]" << "LBA_1 부터 LBA_2 까지의 DATA를 삭제합니다\n";
    out << "  " << std::setw(30) << "flush" << "SSD.exe 프로그램의 Command buffer를 flush 합니다\n";
    out << "  " << std::setw(30) << "fullwrite [DATA]" << "관리하고 있는 모든 주소에 입력받은 DATA를 저장합니다.\n";
    out << "  " << std::setw(30) << "fullread" << "관리하고 있는 모든 주소에 저장되어 있는 값을 읽어옵니다.\n";
    out << "  " << std::setw(30) << "exit" << "프로그램을 종료 합니다\n\n";

    out << "명령어 입력 제약 조건:\n";
    out << std::left;
    out << "  " << std::setw(30) << "[LBA]" << "0~99, A~F, 0~9 까지 숫자 범위만 허용\n";
    out << "  " << std::setw(30) << "[DATA]" << "항상 0x가 붙으며 10 글자로 표기한다. (0x00000000 ~0xFFFFFFFF)\n";
    out << "  " << std::setw(30) << "[SIZE]" << "10진수 숫자 범위로 입력(0~99)\n\n";

    out << "테스트 명령어:\n";
    out << "  " << std::setw(30) << "1_FullWriteAndReadCompare"
        << "모든 주소에 입력받은 값을 쓴 뒤 다시 읽어와 비교해본다.\n";
    out << "  " << std::setw(30) << "2_PartialLBAWrite"
        << "특정 주소들에 입력받은 값을 동일하게 쓰고 다시 읽어와 비교해본다.\n";
    out << "  " << std::setw(30) << "3_WriteReadAging"
        << "특정 주소에 랜덤한 값을 쓰고 다시 읽어와 비교해본다.\n";
    out << "  " << std::setw(30) << "4_EraseAndWriteAging"
        << "특정 주소에 Write,OverWrite를 진행하며 0~97 LBA까지 진행하며 이를 30회 반복한다.\n\n";

    out << "결과 파일 위치:\n";
    out << std::left;
    out << "  " << std::setw(20) << "ssd_nand.txt" << " 0~99 LBA까지의 현재 DATA(정확한 확인은 flush 명령어 수행 후 조회하세요)\n";
    out << "  " << std::setw(20) << "ssd_output.txt" << " read 한 결과 파일\n";
    out << "  " << std::setw(20) << "\\Log" << " Test가 진행된 Log 파일 경로(latest.txt 가 가장 마지막 Log)\n";
    out << "  " << std::setw(20) << "\\buffer" << " Nand에 기록되기전 상태의 Command Buffer 확인\n\n";

    out << "version : SSD_V01_250521 / TestShell_V01_250522\n";
    out << "git source : https://github.com/wnsdud6992/TestShell\n";

    out << std::endl;
}

void TestShell::write(unsigned int address, unsigned int data){
    Logger::LogPrint("TestShell", __func__, "write start " + std::to_string(address) + " " + std::to_string(data));
	driver->write(address, data);
    Logger::LogPrint("TestShell", __func__, "write end");
}

void TestShell::fullwrite(unsigned int data) {
    Logger::LogPrint("TestShell", __func__, "fullwrite start " + std::to_string(data));
    for(unsigned int address_index = ADDRESS_RANGE_MIN; address_index <= ADDRESS_RANGE_MAX; address_index++){
        driver->write(address_index, data);
    }
    Logger::LogPrint("TestShell", __func__, "fullwrite end");
}

unsigned int TestShell::read(unsigned int address) {
    Logger::LogPrint("TestShell", __func__, "read start " + std::to_string(address));
    unsigned int readData = driver->read(address);
    Logger::LogPrint("TestShell", __func__, "read end");
    return readData;
}

std::vector<unsigned int> TestShell::fullread() {
    Logger::LogPrint("TestShell", __func__, "fullread start");
    std::vector<unsigned int> readDataList;
    out << "[Full Read: LBA 0 ~ 99]" << std::endl;

    for (unsigned int lba = 0; lba < 100; ++lba) {
        out << " [LBA " << std::dec << lba << "] ";
        unsigned int data = driver->read(lba);
        readDataList.push_back(data);
    }
    Logger::LogPrint("TestShell", __func__, "fullread end");
    return readDataList;
}

bool TestShell::readCompare(unsigned int address, unsigned int value) {
    return read(address) == value;
}

void TestShell::erase(unsigned int address, int size) {
    Logger::LogPrint("TestShell", __func__, "erase start " + std::to_string(address) + " " + std::to_string(size));
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
    Logger::LogPrint("TestShell", __func__, "erase end");
}

void TestShell::erase_range(unsigned int start_address, unsigned int end_address) {
    Logger::LogPrint("TestShell", __func__, "erase_range start " + std::to_string(start_address) + " " + std::to_string(end_address));
    if (start_address > end_address)
        std::swap(start_address, end_address);
    int size = (end_address - start_address) + 1;

    runEraseCommand(start_address, size);
    Logger::LogPrint("TestShell", __func__, "erase_range end");
}

void TestShell::flush() {
    Logger::LogPrint("TestShell", __func__, "flush start");
    driver->flush();
    Logger::LogPrint("TestShell", __func__, "flush end");
}

bool TestShell::Script1() {
    Logger::LogPrint("TestShell", __func__, "Script1 start");
    for (int loopCnt = 0; loopCnt < Script1_TotalLoopCount; ++loopCnt) {
        writeFive(loopCnt);
        if (readCompareFive(loopCnt) == false) {
            out << "FAIL " << std::endl;
            Logger::LogPrint("TestShell", __func__, "Script1 Fail" + std::to_string(loopCnt));
            return false;
        }
    }
    out << "PASS" << std::endl;
    Logger::LogPrint("TestShell", __func__, "Script1 end");
    return true;
}

bool TestShell::Script2() {
    Logger::LogPrint("TestShell", __func__, "Script2 start");
  
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
                Logger::LogPrint("TestShell", __func__, "Script2 Fail" + std::to_string(address) + " " + std::to_string(data));
                return false;
            }
        }
    }
    out << "PASS" << std::endl;
    Logger::LogPrint("TestShell", __func__, "Script2 end");
    return true;
}

bool TestShell::Script3(){
    Logger::LogPrint("TestShell", __func__, "Script3 start");

    for (int loop = 0; loop < Script3_TotalLoopCount; loop++) {
        srand(RAND_SEED + loop);
        unsigned int randomData = (std::rand() << 16) | std::rand();
        driver->write(ADDRESS_RANGE_MIN, randomData);
        driver->write(ADDRESS_RANGE_MAX, randomData);

        if (!(readCompare(ADDRESS_RANGE_MIN, randomData) && readCompare(ADDRESS_RANGE_MAX, randomData))) {
            out << "FAIL " << std::endl;
            Logger::LogPrint("TestShell", __func__, "Script3 Fail" + std::to_string(randomData));
            return false;
        }
            
    }
    out << "PASS" << std::endl;
    Logger::LogPrint("TestShell", __func__, "Script3 end");
    return true;
}

bool TestShell::Script4() {
    Logger::LogPrint("TestShell", __func__, "Script4 start");

    driver->erase(0, 3);
    for (unsigned int loopCnt = 0; loopCnt < Script4_TotalLoopCount; loopCnt++) {
        unsigned int data = Script2Test_Value + loopCnt;
        for (unsigned int base_addr = Script4_StartAddress; base_addr <= Script4_EndAddress; base_addr += 2){
            driver->write(base_addr, data);
            if (!readCompare(base_addr, data)) {
                out << "FAIL " << std::endl;
                Logger::LogPrint("TestShell", __func__, "Script4 Fail" + std::to_string(base_addr) + " " + std::to_string(data));
                return false;
            }
            driver->write(base_addr, data+1);
            if (!readCompare(base_addr, data + 1)) {
                out << "FAIL " << std::endl;
                Logger::LogPrint("TestShell", __func__, "Script4 Fail" + std::to_string(base_addr) + " " + std::to_string(data+1));
                return false;
            }
            driver->erase(base_addr, 3);
            for (unsigned int erase_addr = 0; erase_addr < 3; ++erase_addr) {
                if (!readCompare(base_addr + erase_addr, 0x00000000)) {
                    out << "FAIL " << std::endl;
                    Logger::LogPrint("TestShell", __func__, "Script4 Fail" + std::to_string(base_addr + erase_addr) + " 0x00000000");
                    return false;
                }
            }
        }
    }
    out << "PASS" << std::endl;
    Logger::LogPrint("TestShell", __func__, "Script4 end");
    return true;
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

void TestShell::writeFive(int loopCnt){
    for (int iter = 0; iter < Script1_OnceLoopCount; iter++) {
        unsigned int address = loopCnt * Script1_OnceLoopCount + iter;
        unsigned int expectedValue = ScriptTest_Value + loopCnt;
        write(address, expectedValue);
    }
}

bool TestShell::readCompareFive(int loopCnt) {
    for (int iter = 0; iter < Script1_OnceLoopCount; iter++) {
        unsigned int address = loopCnt * Script1_OnceLoopCount + iter;
        unsigned int expectedValue = ScriptTest_Value + loopCnt;
        if (read(address) != expectedValue) {
            return false;
        }
    }
    return true;
}

