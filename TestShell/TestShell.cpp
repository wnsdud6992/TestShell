#include "TestShell.h"
#include <iostream>

TestShell::TestShell(IDriver* driver_) : driver(driver_) {}

void TestShell::write(std::vector<unsigned int> command_param){
    if (command_param.size() != 2) {
        throw std::exception("write command argument error");
        return;
    }

    unsigned int address = command_param[0];
    unsigned int data = command_param[1];
	driver->write(address, data);
}


void TestShell::help() {
    std::cout << "\n���� : Critical Coders\n";
    std::cout << "������ : ���ؿ�, ������, ����, �̾Ƴ׽�, �չα�, ��ȿ��\n\n";

    std::cout << "Ư�� ��ɾ ���� �ڼ��� ������ �ʿ��ϸ� HELP <��ɾ� �̸�>�� �Է��Ͻʽÿ�.\n\n";

    std::cout << "�⺻ ��ɾ�:\n";
    std::cout << std::left;
    std::cout << "  " << std::setw(20) << "Write" << "�Է¹��� �ּҿ� �Է¹��� ���� �����մϴ�.\n";
    std::cout << "  " << std::setw(20) << "Read" << "�Է¹��� �ּҿ� ����Ǿ� �ִ� ���� �о�ɴϴ�.\n";
    std::cout << "  " << std::setw(20) << "fullwrite" << "�����ϰ� �ִ� ��� �ּҿ� �Է¹��� ���� �����մϴ�.\n";
    std::cout << "  " << std::setw(20) << "fullread" << "�����ϰ� �ִ� ��� �ּҿ� ����Ǿ� �ִ� ���� �о�ɴϴ�.\n\n";

    std::cout << "�׽�Ʈ ��ɾ�:\n";
    std::cout << "  " << std::setw(30) << "1_FullWriteAndReadCompare"
        << "��� �ּҿ� �Է¹��� ���� �� �� �ٽ� �о�� ���غ���.\n";
    std::cout << "  " << std::setw(30) << "2_PartialLBAWrite"
        << "Ư�� �ּҵ鿡 �Է¹��� ���� �����ϰ� ���� �ٽ� �о�� ���غ���.\n";
    std::cout << "  " << std::setw(30) << "3_WriteReadAging"
        << "Ư�� �ּҿ� ������ ���� ���� �ٽ� �о�� ���غ���.\n";

    std::cout << std::endl;
}

std::pair<std::string, std::vector<unsigned int>> TestShell::parameterParsing(std::string & param) {
    std::vector<unsigned int> parameter;
    std::string command;
    std::istringstream iss(param);

    if (iss >> command) {
        std::string token;
        while (iss >> token) {
            parameter.push_back(std::stoul(token, nullptr, 0));
        }
    }
    if (std::find(validCommands.begin(), validCommands.end(), command) == validCommands.end()) {
        throw CustomException("INVALID COMMAND");
    }
    return { command, parameter };
}

unsigned int TestShell::read(std::vector<unsigned int> address) {
    if (address.size() != 1)
        std::cerr << "INVALID COMMAND \n";
    if (address[0] < 0 || address[0] > 99)
        std::cerr << "INVALID COMMAND \n";

    return driver->read(address[0]);
}

std::vector<unsigned int> TestShell::fullread() {
    std::vector<unsigned int> readDataList;
    std::cout << "[Full Read: LBA 0 ~ 99]" << std::endl;

    for (unsigned int lba = 0; lba < 100; ++lba) {
        readDataList.push_back(driver->read(lba));
        std::cout << "LBA " << lba << " : 0x"
            << std::hex << readDataList[lba] << std::dec << " (" << readDataList[lba] << ")\n";
    }
    return readDataList;
}

bool TestShell::readCompare(std::vector<unsigned int >address, unsigned int value) {
    int readData = read(address);
    return readData == value;
}