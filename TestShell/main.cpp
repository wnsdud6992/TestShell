

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
                testShell->write(parameter);
            }
            else if (command == "read") {
            }
            else if (command == "help") {
                testShell->help();
            }
            else if (command == "exit") {
                std::cout << "Thank you and bye~";
                break;
            }
            else if (command == "1_FullWriteAndReadCompare" || command == "1_") {
                testShell->Script1();
                std::cout << "Thank you and bye~";
                break;
            }
        }
        catch (const CustomException& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
#endif
}