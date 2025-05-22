#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

class EraseFixture : public Test {
public:
	MockDriver mockdriver;
	std::unique_ptr<MockDriver> driver = std::make_unique<MockDriver>();
	std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(driver));

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

TEST_F(EraseFixture, DISABLED_ZeroErase) {
	EXPECT_CALL(mockdriver, erase(_, _)).Times(0);
	testShell->erase(LBA_0, SIZE_0);
	EXPECT_THROW(testShell->erase(100, SIZE_1), CustomException);

}
TEST_F(EraseFixture, DISABLED_NormalErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testShell->erase(LBA_0, SIZE_10);

}
TEST_F(EraseFixture, DISABLED_MinusSizeErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testShell->erase(LBA_9, MINUS_SIZE_10);

}
TEST_F(EraseFixture, DISABLED_MinusSizeUnderAddressErase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_1)).Times(1);
	testShell->erase(LBA_0, MINUS_SIZE_10);

}
TEST_F(EraseFixture, DISABLED_SIZE11Erase) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	EXPECT_CALL(mockdriver, erase(LBA_10, SIZE_1)).Times(1);
	testShell->erase(LBA_0, SIZE_11);

}
TEST_F(EraseFixture, DISABLED_LastAddressSize10Erase) {
	EXPECT_CALL(mockdriver, erase(MAX_LBA, SIZE_1)).Times(1);
	testShell->erase(MAX_LBA, SIZE_11);

}

TEST_F(EraseFixture, DISABLED_SIZE10EraseRange) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testShell->erase_range(LBA_0, LBA_9);

}
TEST_F(EraseFixture, DISABLED_SIZEMinus10EraseRange) {
	EXPECT_CALL(mockdriver, erase(LBA_0, SIZE_10)).Times(1);
	testShell->erase_range(LBA_9, LBA_0);

}
TEST_F(EraseFixture, DISABLED_EraseTestPDF) {
	EXPECT_CALL(mockdriver, erase(4, 2)).Times(1);
	testShell->erase(5, -2);
	EXPECT_CALL(mockdriver, erase(5, 1)).Times(1);
	testShell->erase(5, -1);
	EXPECT_CALL(mockdriver, erase(20, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(30, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(40, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(50, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(60, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(70, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(80, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(90, 10)).Times(1);
	testShell->erase(20, 99);
	EXPECT_CALL(mockdriver, erase(0, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(10, 10)).Times(1);
	EXPECT_CALL(mockdriver, erase(20, 1)).Times(1);
	testShell->erase(20, -99);
}

TEST_F(EraseFixture, DISABLED_flushTest) {
	EXPECT_CALL(mockdriver, flush).Times(1);
	testShell->flush();

}