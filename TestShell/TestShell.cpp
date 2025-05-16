#include "TestShell.h"

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
