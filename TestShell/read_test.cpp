#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ReadTest, ReadSuccess) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::vector<unsigned int> address = { 20 };
	EXPECT_CALL(mockdriver, read(20)).Times(1).WillRepeatedly(Return(0xAAAABBBB));
	EXPECT_EQ(0xAAAABBBB, testshell.read({ address }));
}

TEST(FullreadTest, FullreadSuccess) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	int mockReturnvalue = 0xAAAABBBB;
	for (int lba = 0; lba < 100; ++lba) {
		std::vector<unsigned int> address{ static_cast<unsigned int>(lba) };
		EXPECT_CALL(mockdriver, read(lba)).WillRepeatedly(Return(mockReturnvalue));
		EXPECT_EQ(mockReturnvalue, testshell.read({ address }));
	}
}