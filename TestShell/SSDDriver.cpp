#include "SSDDriver.h"

void SSDDriver::write(unsigned int address, unsigned int value) {
	std::string SSD_exe_Writeparam = "";
	std::ostringstream oss;
	oss << "w " << address << " " << toHexString(value);
	SSD_exe_Writeparam += oss.str();
	runSSDWithParam(SSD_exe_Writeparam);
}
unsigned int SSDDriver::read(unsigned int address) {
	std::string SSD_exe_Readparam = "";
	std::ostringstream oss;
	oss << "r " << address;
	SSD_exe_Readparam += oss.str();
	runSSDWithParam(SSD_exe_Readparam);

	return readSSDOutputFile();
}

void SSDDriver::runSSDWithParam(const std::string& param) {
	std::filesystem::path exePath = std::filesystem::current_path() / "SSD.exe";
	std::string command = "\"" + exePath.string() + "\" " + param;
	int result = std::system(command.c_str());
	std::cout << "Exit code: " << result << std::endl;
}

unsigned int SSDDriver::readSSDOutputFile() {
	std::ifstream inputFile(SSD_OutPutFile);

	if (!inputFile) {
		throw CustomException("파일을 열 수 없습니다");
	}

	unsigned int readvalue;
	if (inputFile >> readvalue) {
		std::cout << "읽은 값: " << readvalue << std::endl;
	}
	else {
		throw CustomException("파일에서 값을 읽을 수 없습니다.");
	}

	inputFile.close();
	return readvalue;
}