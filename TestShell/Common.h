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
#include <variant>

using ParamType = std::variant<unsigned int, int>;

const std::string SSD_OutPutFile = "ssd_output.txt";
const std::string LogDir = "C:\\Users\\User\\source\\repos\\TestShell\\x64\\Release\\Log";
const std::string LogFileName = "latest.log";
constexpr std::uintmax_t LogFileMaxSize = 10 * 1024;

const std::string SSDexe_Path = "C:\\Users\\User\\source\\repos\\TestShell\\x64\\Release\\SSD.exe";

class CustomException : public std::exception {
public:
	explicit CustomException(char const* message) : exception{ message } {}
};

inline std::vector<std::string> validCommands = {
"write", "read", "exit", "help", "fullwrite", "fullread", 
"1_", "1_FullWriteAndReadCompare", 
"2_", "2_PartialLBAWrite", 
"3_", "3_WriteReadAging", 
"4_", "4_EraseAndWriteAging", 
"erase", "erase_range", "flush"
};

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

inline std::string toHexString(unsigned int value) {
    std::stringstream ss;
    ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << value;
    return ss.str();
}

constexpr int Script4_TotalLoopCount = 30;
constexpr unsigned int Script4Test_Value = 0x1289CDEF;
constexpr unsigned int Script4_StartAddress = 2;
constexpr unsigned int Script4_EndAddress = 96;


enum class driverType {
    SSD,
    HDD,
    SD_Card,
    eMMC,
    Mock,
};