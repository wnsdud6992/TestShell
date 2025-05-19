#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <cstdlib>
#include <fstream>

class CustomException : public std::exception {
public:
    explicit CustomException(char const* message) : exception{ message } {}
};

inline std::vector<std::string> validCommands = {
    "write", "read", "exit", "help", "fullwrite", "fullread", "1_", "1_FullWriteAndReadCompare", "2_", "2_PartialLBAWrite", "3_", "3_WriteReadAging"
};

constexpr int Script1_TotalLoopCount = 20;
constexpr int Script1_OnceLoopCount = 5;
constexpr unsigned int ScriptTest_Value = 0x1289CDEF;
const std::string SSD_OutPutFile = "ssd_output.txt";

inline std::string toHexString(unsigned int value) {
    std::stringstream ss;
    ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << value;
    return ss.str();
}