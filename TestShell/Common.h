#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <algorithm>

const std::string SSD_OutPutFile = "ssd_output.txt";
const std::string LogDir = ".\\Log";
const std::string LogFileName = "latest.log";
constexpr std::uintmax_t LogFileMaxSize = 10 * 1024;
const std::string SSDexe_Path = ".\\SSD.exe";



constexpr const int MAX_ERASE_SIZE = 10;
constexpr unsigned int ADDRESS_RANGE_MIN = 0;
constexpr unsigned int ADDRESS_RANGE_MAX = 99;
const int RAND_SEED = 99;
constexpr int Script1_TotalLoopCount = 20;
constexpr int Script1_OnceLoopCount = 5;
constexpr unsigned int ScriptTest_Value = 0x1289CDEF;
constexpr int Script2_TotalLoopCount = 30;
constexpr unsigned int Script2_Address[5] = { 4, 0, 3, 1, 2 };
constexpr unsigned int Script2Test_Value = 0x1289CDEF;
constexpr int Script3_TotalLoopCount = 200;
constexpr int Script4_TotalLoopCount = 30;
constexpr unsigned int Script4Test_Value = 0x1289CDEF;
constexpr unsigned int Script4_StartAddress = 2;
constexpr unsigned int Script4_EndAddress = 96;

class CustomException : public std::exception {
public:
	explicit CustomException(char const* message) : exception{ message } {}
};

inline std::string toHexString(unsigned int value) {
	std::stringstream ss;
	ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << value;
	return ss.str();
}

inline unsigned int stringToUint(std::string str)
{
	try {
		return std::stoul(str, nullptr, 0);
	}
	catch (const std::invalid_argument&) {
		throw CustomException((std::string("[Error] 숫자로 변환할 수 없는 문자열: ") + str).c_str());
	}
	catch (const std::out_of_range&) {
		throw CustomException((std::string("[Error] 숫자가 너무 큽니다: ") + str).c_str());
	}
}

enum class driverType {
    SSD = 1,
    HDD,
    SD_Card,
    eMMC,
    Mock,
};

inline std::map<driverType, std::string> enumDriverTypeToStr{
	{driverType::SSD, "SSD Driver"},
	{driverType::HDD, "HDD Driver"},
	{driverType::SD_Card, "SD_Card Driver"},
	{driverType::eMMC, "eMMC Driver"},
	{driverType::Mock, "Mock Driver"},
};