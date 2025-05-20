#include "TestShell.h"
#include "SSDDriver.h"
#include "Runner.h"
#include "CommandFactory.h"

int main() {
#ifdef _DEBUG 
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
#else  
    std::cout << "Welcome to Critical Coders's Test Shell!!" << std::endl << std::endl;
    std::cout << "What kind of driver do you want to test?" << std::endl;
    std::cout << "1.SSD   2.HDD   3.SD Card   4.eMMC" << std::endl << std::endl;
    SSDDriver ssdDriver;
    SSDDriver runnerSsdDriver;
    std::ostringstream dummyOut;
    runnerSsdDriver.setoutput(&dummyOut);

    std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(&ssdDriver); // todo 추후 factory화 하여 사용자로부터 입력받은 driver로 실행
    TestShell runnerTestShell(&runnerSsdDriver, dummyOut);
    std::unique_ptr<Runner> runner = std::make_unique<Runner>(&runnerTestShell);
    std::unique_ptr<TestShellCommandFactory> testShellCmdFactory = std::make_unique<TestShellCommandFactory>(testShell);

    std::string userInput;
    while (true) {
        std::cout << "Shell> ";
        try {
            std::getline(std::cin, userInput);
            testShellCmdFactory->executeCommand(userInput);
        }
        catch (const CustomException& e) {
            std::cout << e.what() << std::endl;
        }
        Sleep(10);
    }
    return 0;
#endif
}

