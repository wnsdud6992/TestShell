

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
        std::getline(std::cin, userInput);

        auto [command, parameter] = testShell->parameterParsing(userInput);

        if (command == "write") {
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
        else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }
    return 0;
#endif
}