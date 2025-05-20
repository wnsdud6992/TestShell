#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

TEST(Script3WriteReadAging, DISABLED_NormalPass) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	srand(RAND_SEED);
	unsigned int random_number = (std::rand() << 16) | std::rand();
	EXPECT_CALL(mockdriver, write(ADDRESS_RANGE_MIN, random_number)).Times(Script3_TotalLoopCount);
	EXPECT_CALL(mockdriver, write(ADDRESS_RANGE_MAX, random_number)).Times(Script3_TotalLoopCount);
	EXPECT_CALL(mockdriver, read(ADDRESS_RANGE_MIN)).Times(Script3_TotalLoopCount).WillRepeatedly(Return(random_number));
	EXPECT_CALL(mockdriver, read(ADDRESS_RANGE_MAX)).Times(Script3_TotalLoopCount).WillRepeatedly(Return(random_number));
	
	EXPECT_TRUE(testshell.Script3());

}

TEST(Script3WriteReadAging, NotSameReadFail) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	srand(RAND_SEED);
	unsigned int random_number = (std::rand() << 16) | std::rand();
	EXPECT_CALL(mockdriver, write(ADDRESS_RANGE_MIN, random_number)).Times(1);
	EXPECT_CALL(mockdriver, write(ADDRESS_RANGE_MAX, random_number)).Times(1);
	EXPECT_CALL(mockdriver, read(ADDRESS_RANGE_MIN)).Times(1).WillRepeatedly(Return(0));
	
	EXPECT_FALSE(testshell.Script3());

}