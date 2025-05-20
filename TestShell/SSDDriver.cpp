#include "SSDDriver.h"

void SSDDriver::write(unsigned int address, unsigned int value) {
	std::string SSD_exe_Writeparam = "";
	std::ostringstream oss;
	oss << "W " << address << " " << toHexString(value);
	SSD_exe_Writeparam += oss.str();
	runSSDWithParam(SSD_exe_Writeparam);
}
unsigned int SSDDriver::read(unsigned int address) {
	std::string SSD_exe_Readparam = "";
	std::ostringstream oss;
	oss << "R " << address;
	SSD_exe_Readparam += oss.str();
	runSSDWithParam(SSD_exe_Readparam);

	return readSSDOutputFile();
}

void SSDDriver::setOutput(std::ostream* output){
	this->out = output;
}

void SSDDriver::runSSDWithParam(const std::string& param) {
	std::string path = "C:\\Users\\User\\source\\repos\\TestShell\\TestShell\\SSD.exe";
	std::string command = "\"" + path + "\" " + param;
	if (out) {
		*out << "Command: " << command << std::endl;
	}
	int result = std::system(command.c_str());
	// std::cout << "Exit code: " << result << std::endl;
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
	return std::stoul(readvalue, nullptr, 0);
}