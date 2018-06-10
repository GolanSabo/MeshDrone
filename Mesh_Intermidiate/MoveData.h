#pragma once
#include "Data.h"
#include <SPI.h>
//#include "Utils.h"
class MoveData :
	public Data
{
	int _amount;
	int _direction;
public:
	MoveData();
	MoveData(int direction, int amount);
	MoveData(String data);
	int getAmount();
	int getDirection();
	void setAmount(int amount);
	void setDirection(int direction);
	void printData();
	String toString();
	void parseData(String str);
	~MoveData();
};

