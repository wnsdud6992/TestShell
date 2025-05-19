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