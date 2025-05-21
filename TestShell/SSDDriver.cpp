#include "SSDDriver.h"

void SSDDriver::runFunc(const std::string cmd_digit, const unsigned int param1 = 0, const  unsigned int param2 = 0)
{
	const unsigned int address = param1;
	const unsigned int address2 = param2;
	const unsigned int value = param2;
	std::ostringstream oss;
	oss << "\"" << SSDexe_Path << "\" " << cmd_digit << " ";
	if (cmd_digit == "W") {
		oss << address << " " << toHexString(value);
	}
	else if (cmd_digit == "R") {
		oss << address << " ";
	}
	else if (cmd_digit == "E") {
		oss << address << " " << address2;

	}
	else if (cmd_digit == "F") {
		; //nothing
	}
	else {
		throw CustomException("undefined command for call SSD.exe run");
	}

	std::system(oss.str().c_str());
}

void SSDDriver::write(unsigned int address, unsigned int value) {
	runFunc("W", address, value);
}

unsigned int SSDDriver::read(unsigned int address) {
	runFunc("R", address);
	return readSSDOutputFile();
}

void SSDDriver::erase(unsigned int address, unsigned int size) {
	if (size > MAX_ERASE_SIZE || size < 0) {
		throw CustomException("Erase size range error");
	}
	runFunc("E", address, size);
}

void SSDDriver::flush() {
	runFunc("F");
}

void SSDDriver::setoutput(std::ostream* output){
	this->out = output;
}

unsigned int SSDDriver::readSSDOutputFile() {
	std::ifstream inputFile(SSD_OutPutFile);

	if (!inputFile) {
		throw CustomException("파일을 열 수 없습니다");
	}

	std::string readvalue;
	if (inputFile >> readvalue && out) {
		*out << "읽은 값: " << readvalue << std::endl;
	}
	else {
		throw CustomException("파일에서 값을 읽을 수 없습니다.");
	}

	inputFile.close();

	unsigned int result_readvalue = 0;
	try {
		result_readvalue = std::stoul(readvalue, nullptr, 0);
	}
	catch (const std::invalid_argument&) {
		throw CustomException((std::string("[Error] 숫자로 변환할 수 없는 문자열: ") + readvalue).c_str());
	}
	catch (const std::out_of_range&) {
		throw CustomException((std::string("[Error] 숫자가 너무 큽니다: ") + readvalue).c_str());
	}

	return result_readvalue;
}