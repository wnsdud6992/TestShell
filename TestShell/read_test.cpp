#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ReadTest, DISABLED_ReadSuccess) {
	MockDriver mockdriver;
	std::unique_ptr<MockDriver> driver = std::make_unique<MockDriver>();
	std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(driver));
	unsigned int address { 20 };
	unsigned int mockReturnvalue = 0xAAAABBBB;
	EXPECT_CALL(mockdriver, read(address)).Times(1).WillRepeatedly(Return(mockReturnvalue));
	EXPECT_EQ(mockReturnvalue, testShell->read(address));
}

TEST(FullreadTest, DISABLED_FullreadSuccess) {
	MockDriver mockdriver;
	std::unique_ptr<MockDriver> driver = std::make_unique<MockDriver>();
	std::unique_ptr<TestShell> testShell = std::make_unique<TestShell>(std::move(driver));
	unsigned int mockReturnvalue = 0xAAAABBBB;
	for (unsigned int lba = 0; lba < 100; ++lba) {
		EXPECT_CALL(mockdriver, read(lba)).WillRepeatedly(Return(mockReturnvalue));
		EXPECT_EQ(mockReturnvalue, testShell->read(lba));
	}
}