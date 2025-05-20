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
	const unsigned int LBA_20 = 20;
	const unsigned int MAX_LBA = 100 - 1;
	const unsigned int SIZE_0 = 0;
	const unsigned int SIZE_1 = 1;
	const unsigned int SIZE_10 = 10;
	const unsigned int SIZE_11 = 11;
	const unsigned int SIZE_99 = 99;
	const int MINUS_SIZE_10 = -10;
	const int MINUS_SIZE_99 = -99;
};

TEST_F(EraseFixture, ZeroErase) {
	EXPECT_CALL(mockdriver, erase(_, _)).Times(0);
	testshell.erase(LBA_0, SIZE_0);
	EXPECT_THROW(testshell.erase(100, SIZE_1), CustomException);

}
TEST_F(EraseFixture, NormalErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase(LBA_0, SIZE_10);

}
TEST_F(EraseFixture, MinusSizeErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase(LBA_9, MINUS_SIZE_10);

}
TEST_F(EraseFixture, MinusSizeUnderAddressErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_1)).Times(1);
	testshell.erase(LBA_0, MINUS_SIZE_10);

}
TEST_F(EraseFixture, SIZE11Erase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	EXPECT_CALL(mockdriver, erase(LBA_10, SIZE_1)).Times(1);
	testshell.erase(LBA_0, SIZE_11);

}
TEST_F(EraseFixture, LastAddressSize10Erase) {
	EXPECT_CALL(mockdriver, erase(MAX_LBA, SIZE_1)).Times(1);
	testshell.erase(MAX_LBA, SIZE_11);

}

TEST_F(EraseFixture, SIZE10EraseRange) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase_range(LBA_0, LBA_9);

}
TEST_F(EraseFixture, SIZEMinus10EraseRange) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testshell.erase_range(LBA_9, LBA_0);

}
TEST_F(EraseFixture, EraseTestPDF) {
	EXPECT_CALL(mockdriver, erase(4, 2)).Times(1);
	testshell.erase(5, -2);
	EXPECT_CALL(mockdriver, erase(5, 1)).Times(1);
	testshell.erase(5, -1);
	EXPECT_CALL(mockdriver, erase(20, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(30, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(40, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(50, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(60, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(70, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(80, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(90, 10)).Times(1);
	testshell.erase(20, 99);
	EXPECT_CALL(mockdriver, erase(0, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(10, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(20, 1)).Times(1);
	testshell.erase(20, -99);
}