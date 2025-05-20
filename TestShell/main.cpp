

#include "TestShell.h"
#include "SSDDriver.h"
int main() {
#ifdef _DEBUG 
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
#else  
    std::cout << "Welcome to Critical Coders's Test Shell!!" << std::endl << std::endl;
    std::cout << "What kind of driver do you want to test?" << std::endl;
    std::cout << "1.SSD   2.HDD   3.SD Card   4.eMMC" << std::endl << std::endl;
    SSDDriver ssdDriver;
    std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(&ssdDriver); // todo 추후 factory화 하여 사용자로부터 입력받은 driver로 실행
    std::string userInput;
    while (true) {
        std::cout << "Shell> ";
        try {
            std::getline(std::cin, userInput);

            auto [command, parameter] = testShell->parameterParsing(userInput);

            if (command == "write") {
                auto [address, data] = testShell->CheckWriteParamValid(parameter);
                testShell->write(address, data);
            }
            else if (command == "read") {
              unsigned int address = testShell->CheckReadParamValid(parameter);
              testShell->read(address);
            }
            else if (command == "help") {
                testShell->help();
            }
            else if (command == "fullwrite") {
                unsigned int data = testShell->CheckFullWriteParamValid(parameter);
                testShell->fullwrite(data);
            }
            else if (command == "fullread") {
                testShell->fullread();
            }
            else if (command == "1_FullWriteAndReadCompare" || command == "1_") {
                testShell->Script1();
            }
            else if (command == "2_PartialLBAWrite" || command == "2_") {
                testShell->Script2();
            }
            else if (command == "3_WriteReadAging" || command == "3_") {
                testShell->Script3();
            }
            else if (command == "4_EraseAndWriteAging" || command == "4_") {
                testShell->Script4();
            }
            else if (command == "exit") {
                std::cout << "Thank you and bye~";
                break;
            }
            else {
                std::cout << "Unknown command. Please try again." << std::endl;
            }
        }
        catch (const CustomException& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
#endif
}

