#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ReadTest, ReadSuccess) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	EXPECT_CALL(mockdriver, read(20)).Times(1);
	EXPECT_TRUE(testshell.read(20));
}

TEST(FullreadTest, FullreadSuccess) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	int mockReturnvalue = 0xAAAABBBB;
	for (int lba = 0; lba < 100; ++lba) {
		EXPECT_CALL(mockdriver, read(lba)).Times(1).WillRepeatedly(::testing::Return(mockReturnvalue));
		EXPECT_EQ(mockReturnvalue, 0xAAAABBBB);
	}
	EXPECT_TRUE(testshell.fullread());
}