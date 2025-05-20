#include "gmock/gmock.h"
#include "MockDriver.h"
#include "TestShell.h"
using namespace testing;

class ParsingFixture : public Test {
public:
	MockDriver mockdriver;
	TestShell testshell{ &mockdriver };
	std::string ReadStr = "read 20";
	std::string WriteStr = "write 3 0x1289CDEF";
	std::string InvalidCommandStr = "wrote 3 0x1289CDEF 0x1289AAAF";
	
};

TEST_F(ParsingFixture, TestRead) {	
	auto [cmd, param] = testshell.commandParsing(ReadStr);
	std::vector<unsigned int> parameter = testshell.normalParamParsing(param);
	EXPECT_EQ("read", cmd);
	EXPECT_EQ(20, parameter[0]);
}

TEST_F(ParsingFixture, TestWrite) {
	auto [cmd, param] = testshell.commandParsing(WriteStr);
	std::vector<unsigned int> parameter =testshell.normalParamParsing(param);
	EXPECT_EQ("write", cmd);
	EXPECT_EQ(3, parameter[0]);
	EXPECT_EQ(static_cast<unsigned int>(0x1289CDEF), parameter[1]);
}


TEST_F(ParsingFixture, InvalidCommand) {
	auto [cmd, param] = testshell.commandParsing(InvalidCommandStr);
	std::vector<unsigned int> parameter = testshell.normalParamParsing(param);
	EXPECT_THROW(testshell.CheckWriteParamValid(parameter), CustomException);
}