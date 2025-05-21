#include "TestShell.h"
#include "SSDDriver.h"
#include "Runner.h"
#include "CommandFactory.h"
#include "DriverFactory.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG 
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
#else  
    std::cout << "Welcome to Critical Coders's Test Shell!!" << std::endl << std::endl;

    /* Runner mode */
    if (argc == 2) {
        std::ostringstream dummyOut;
        std::unique_ptr<SSDDriver> runnerSsdDriver = std::make_unique<SSDDriver>();
        runnerSsdDriver->setoutput(&dummyOut);
        std::unique_ptr<TestShell> runnerTestShell = std::make_unique<TestShell>(std::move(runnerSsdDriver), dummyOut);
        std::unique_ptr<Runner> runner = std::make_unique<Runner>(runnerTestShell.get());

        Logger::LogPrint("main", "main", "Runner Mode selected");
        std::string runCommand = argv[1];
        runner->runFromFile(runCommand);
        return 0;
    }

    /* Normal mode */
    std::string InputDriverType = "";
    std::unique_ptr<IDriver> userDriver;
    while (true) {
        std::cout << "What kind of driver do you want to test?" << std::endl;
        std::cout << "1.SSD   2.HDD   3.SD Card   4.eMMC   5.Mock" << std::endl << std::endl;
        std::cout << "Shell> ";
        std::getline(std::cin, InputDriverType);
        userDriver = DriverFactory::driverFactory(InputDriverType);
        if (userDriver != nullptr) break;
    }

    std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(userDriver));
    std::unique_ptr<CommandFactory> CmdFactory = std::make_unique<CommandFactory>();

    std::cout << "TestShell Start with "<< enumDriverTypeToStr[static_cast<driverType>(std::stoi(InputDriverType))] << "!!!" << std::endl << std::endl;
    std::string userInput;
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

