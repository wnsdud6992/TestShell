#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

class EraseFixture : public Test {
public:
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	const unsigned int NORMAL_ADDRESS = 0;
	const unsigned int MAX_LBA = 100 - 1;
	const unsigned int SIZE_10 = 10;
	const int MINUS_SIZE_10 = -10;
};

TEST_F(EraseFixture, NormalErase) {
	EXPECT_CALL(mockdriver, erase(NORMAL_ADDRESS, SIZE_10)).Times(1);
	testshell.erase(NORMAL_ADDRESS, SIZE_10);

}

TEST_F(EraseFixture, MinusSizeErase) {
	EXPECT_CALL(mockdriver, erase(NORMAL_ADDRESS, MINUS_SIZE_10)).Times(1);
	testshell.erase(NORMAL_ADDRESS, MINUS_SIZE_10);

}
