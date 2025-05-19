#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
#include <vector>
using namespace testing;

TEST(Script2, NormalPass) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	srand(RAND_SEED);
	unsigned int random_number = (std::rand() << 16) | std::rand();
	EXPECT_CALL(mockdriver, write(0, random_number)).Times(200);
	EXPECT_CALL(mockdriver, write(99, random_number)).Times(200);
	EXPECT_CALL(mockdriver, read(0)).Times(200).WillRepeatedly(Return(random_number));
	EXPECT_CALL(mockdriver, read(99)).Times(200).WillRepeatedly(Return(random_number));
	
	EXPECT_TRUE(testshell.Script3());

}