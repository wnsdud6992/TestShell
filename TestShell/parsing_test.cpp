#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ParsingTest, b) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::string testStr = "write 3";
	auto [cmd, param] =testshell.parameterParsing(testStr);
	EXPECT_EQ("write", cmd);
	EXPECT_EQ(3, param[0]);
}
