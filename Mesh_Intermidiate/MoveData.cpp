#include "MoveData.h"
MoveData::MoveData()
{
}

MoveData::MoveData(int direction, int amount)
{
	_direction = direction;
	_amount = amount;
	_data = toString();
}

MoveData::MoveData(String data)
{
	_data = data;
	parseData(data);
}

int MoveData::getAmount()
{
	return _amount;
}

int MoveData::getDirection()
{
	return _direction;
}

void MoveData::setAmount(int amount)
{
	_amount = amount;
}

void MoveData::setDirection(int direction)
{
	_direction = direction;
}

void MoveData::printData()
{
	Serial.print("Direction : ");
	Serial.println(getDirection());
	Serial.print("amount: ");
	Serial.println(getAmount());
}

String MoveData::toString() {
	return String(_direction) + ',' + String(_amount);
}


MoveData::~MoveData()
{
}


void MoveData::parseData(String str) {
	_direction = str.substring(0, 1).toInt();
	_amount = str.substring(2, 6).toInt();
}