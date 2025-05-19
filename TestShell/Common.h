#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class CustomException : public std::exception {
public:
    explicit CustomException(char const* message) : exception{ message } {}
};

inline std::vector<std::string> validCommands = {
    "write", "read", "exit", "help", "fullwrite", "fullread", "2_PartialLBAWrite", "2_"
};

constexpr int Script1_TotalLoopCount = 20;
constexpr int Script1_OnceLoopCount = 5;
constexpr unsigned int ScriptTest_Value = 0x1289CDEF;
