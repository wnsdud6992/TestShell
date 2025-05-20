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

void SSDDriver::runSSDWithParam(const std::string& param) {
	std::string path = "C:\\Users\\User\\source\\repos\\TestShell\\TestShell\\SSD.exe";
	std::string command = "\"" + path + "\" " + param;
	std::cout << "Command: " << command << std::endl;
	int result = std::system(command.c_str());
	// std::cout << "Exit code: " << result << std::endl;
}

unsigned int SSDDriver::readSSDOutputFile() {
	std::ifstream inputFile(SSD_OutPutFile);

	if (!inputFile) {
		throw CustomException("파일을 열 수 없습니다");
	}

	std::string readvalue;
	if (inputFile >> readvalue) {
		std::cout << "읽은 값: " << readvalue << std::endl;
	}
	else {
		throw CustomException("파일에서 값을 읽을 수 없습니다.");
	}

	inputFile.close();
	return std::stoul(readvalue, nullptr, 0);
}
void SSDDriver::erase(unsigned int address, unsigned int size) {
	std::string SSD_exe_Eraseparam = "";
	std::ostringstream oss;
	oss << "E " << address << " " << size;
	if (size > MAX_ERASE_SIZE || size < 0) {
		throw CustomException("Erase size range error");
	}
	SSD_exe_Eraseparam += oss.str();
	runSSDWithParam(SSD_exe_Eraseparam);
}
void SSDDriver::flush() {
	std::string SSD_exe_Flushparam = "";
	std::ostringstream oss;
	oss << "F ";
	SSD_exe_Flushparam += oss.str();
	runSSDWithParam(SSD_exe_Flushparam);

}