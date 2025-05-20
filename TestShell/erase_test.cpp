#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

class EraseFixture : public Test {
public:
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	const unsigned int LBA_0 = 0;
	const unsigned int LBA_9 = 9;
	const unsigned int LBA_10 = 10;
	const unsigned int MAX_LBA = 100 - 1;
	const unsigned int SIZE_1 = 1;
	const unsigned int SIZE_10 = 10;
	const unsigned int SIZE_11 = 11;
	const int MINUS_SIZE_10 = -10;
};

TEST_F(EraseFixture, NormalErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase(LBA_0, SIZE_10);

}
TEST_F(EraseFixture, MinusSizeErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, MINUS_SIZE_10)).Times(1);
	testshell.erase(LBA_0, MINUS_SIZE_10);

}
TEST_F(EraseFixture, SIZE10EraseRange) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase_range(LBA_0, LBA_9);

}
TEST_F(EraseFixture, SIZEMinus10EraseRange) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase_range(LBA_9, LBA_0);

}