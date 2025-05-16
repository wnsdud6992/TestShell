#pragma once
#include "IDriver.h"
#include "gmock/gmock.h"

class MockDriver : public IDriver {
public:
	MOCK_METHOD(void, write, (int, int), (override));
	MOCK_METHOD(int, read, (int), (override));
};
