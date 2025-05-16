#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <memory>

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
    std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(&ssdDriver); // todo ���� factoryȭ �Ͽ� ����ڷκ��� �Է¹��� driver�� ����
    std::string userInput;
    while (true) {
        std::cout << "Shell> "; 
        std::getline(std::cin, userInput);

        if (userInput == "����1") {
        }
        else if (userInput == "����2") {
        }
        else if (userInput == "help") {
            break;
        }
        else if (userInput == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }
    return 0;
#endif
}