#pragma once
#include "Common.h"
#include "IDriver.h"
#include "SSDDriver.h"
#include "MockDriver.h"

class DriverFactory {
public:
	static std::unique_ptr<IDriver> driverFactory(std::string &type) {
		std::istringstream iss(type);
		std::vector<std::string> param;
		std::string token;
		while (iss >> token) {
			param.push_back(token);
		}
		if (param.size() != 1) {
			std::cerr << "�������� driver�� �����ϼ̽��ϴ�. �Ѱ��� �������ּ���." << std::endl << std::endl;
			return nullptr;
		}

		driverType Type;
		try {
			Type = static_cast<driverType>(std::stoi(type));
		}
		catch (const std::invalid_argument&) {
			std::cerr << "[Error] ���ڷ� ��ȯ�� �� ���� �����Դϴ�. �ٽ� �Է��ϼ���." << std::endl << std::endl;
			return nullptr;
		}
		catch (const std::out_of_range&) {
			std::cerr << "[Error] ���ڰ� �ʹ� Ů�ϴ�. �ٽ� �Է��ϼ���." << std::endl << std::endl;
			return nullptr;
		}
		
		switch (Type) {
		case driverType::SSD:
			return std::make_unique<SSDDriver>();
		case driverType::HDD:
			return std::make_unique<HDDDriver>();
		case driverType::SD_Card:
			return std::make_unique<SD_CardDriver>();
		case driverType::eMMC:
			return std::make_unique<eMMCDriver>();
		case driverType::Mock:
			return std::make_unique<MockDriver>();
		default:
			std::cout << "Wrong driver type. write again!";
			break;
		}
		return nullptr;
	}
};