#pragma once
#include <WString.h>
class Data {
protected:
	String _data;
public:
	virtual void printData() = 0;
	virtual String toString() = 0;
	virtual void parseData(String str) = 0;
	virtual ~Data() {};
};

