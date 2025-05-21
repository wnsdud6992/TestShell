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
			std::cerr << "여러개의 driver를 선택하셨습니다. 한개만 선택해주세요." << std::endl << std::endl;
			return nullptr;
		}

		driverType Type;
		try {
			Type = static_cast<driverType>(std::stoi(type));
		}
		catch (const std::invalid_argument&) {
			std::cerr << "[Error] 숫자로 변환할 수 없는 문자입니다. 다시 입력하세요." << std::endl << std::endl;
			return nullptr;
		}
		catch (const std::out_of_range&) {
			std::cerr << "[Error] 숫자가 너무 큽니다. 다시 입력하세요." << std::endl << std::endl;
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