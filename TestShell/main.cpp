#include "TestShell.h"
#include "SSDDriver.h"
#include "Runner.h"
#include "CommandFactory.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG 
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
#else  
    std::cout << "Welcome to Critical Coders's Test Shell!!" << std::endl << std::endl;
    std::cout << "What kind of driver do you want to test?" << std::endl;
    std::cout << "1.SSD   2.HDD   3.SD Card   4.eMMC" << std::endl << std::endl;
    SSDDriver ssdDriver;
    std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(&ssdDriver); // todo 추후 factory화 하여 사용자로부터 입력받은 driver로 실행
    
    SSDDriver runnerSsdDriver;
    std::ostringstream dummyOut;
    runnerSsdDriver.setoutput(&dummyOut);
    TestShell runnerTestShell(&runnerSsdDriver, dummyOut);
    std::unique_ptr<Runner> runner = std::make_unique<Runner>(&runnerTestShell);


    std::unique_ptr<CommandFactory> CmdFactory = std::make_unique<CommandFactory>();

    std::string userInput;
    if (argc == 2) {
        std::string runCommand = argv[1];
        runner->runFromFile(runCommand);
        return 0;
    }

    while (true) {
        std::cout << "Shell> ";
        std::getline(std::cin, userInput);

        try {
            auto command = CmdFactory->parse(userInput);
            command->execute(*testShell);
        }
        catch (const CustomException& e) {
            std::cout << e.what() << std::endl;
        }
        Sleep(10);
    }
    return 0;
#endif
}

