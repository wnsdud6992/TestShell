#pragma once
#include "Common.h"
#include "Logger.h"

class IDriver {
public:
	virtual void write(unsigned int address, unsigned int value) = 0;
	virtual unsigned int read(unsigned int address) = 0;
	virtual void setoutput(std::ostream* out) = 0;
	virtual void erase(unsigned int address, unsigned int size) = 0;
	virtual void flush() = 0;
};

class HDDDriver : public IDriver {
public:
	HDDDriver() {}
	void write(unsigned int address, unsigned int value) override {};
	unsigned int read(unsigned int address) override { return 0; };
	void setoutput(std::ostream* output) override {};
	void erase(unsigned int address, unsigned int size) override {};
	void flush() override {};
};

class SD_CardDriver : public IDriver {
public:
	SD_CardDriver() {}
	void write(unsigned int address, unsigned int value) override {};
	unsigned int read(unsigned int address) override { return 0; };
	void setoutput(std::ostream* output) override {};
	void erase(unsigned int address, unsigned int size) override {};
	void flush() override {};
};

class eMMCDriver : public IDriver {
public:
	eMMCDriver() {}
	void write(unsigned int address, unsigned int value) override {};
	unsigned int read(unsigned int address) override { return 0; };
	void setoutput(std::ostream* output) override {};
	void erase(unsigned int address, unsigned int size) override {};
	void flush() override {};
};