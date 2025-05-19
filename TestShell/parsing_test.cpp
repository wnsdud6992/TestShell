#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

TEST(ParsingTest, TestRead) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::string testStr = "read 20 ";
	auto [cmd, param] = testshell.parameterParsing(testStr);
	EXPECT_EQ("read", cmd);
	EXPECT_EQ(20, param[0]);
}

TEST(ParsingTest, TestWrite) {
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::string testStr = "write 3 0x1289CDEF";
	auto [cmd, param] =testshell.parameterParsing(testStr);
	EXPECT_EQ("write", cmd);
	EXPECT_EQ(3, param[0]);
	EXPECT_EQ(static_cast<unsigned int>(0x1289CDEF), param[1]);
}

