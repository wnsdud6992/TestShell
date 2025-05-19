#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ReadTest, ReadSuccess) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	unsigned int address { 20 };
	unsigned int mockReturnvalue = 0xAAAABBBB;
	EXPECT_CALL(mockdriver, read(address)).Times(1).WillRepeatedly(Return(mockReturnvalue));
	EXPECT_EQ(mockReturnvalue, testshell.read(address));
}

TEST(FullreadTest, FullreadSuccess) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	unsigned int mockReturnvalue = 0xAAAABBBB;
	for (unsigned int lba = 0; lba < 100; ++lba) {
		EXPECT_CALL(mockdriver, read(lba)).WillRepeatedly(Return(mockReturnvalue));
		EXPECT_EQ(mockReturnvalue, testshell.read(lba));
	}
}