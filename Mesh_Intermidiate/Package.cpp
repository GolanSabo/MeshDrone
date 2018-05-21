#include "Package.h"

//Package::Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, Vector<byte> data)
//	:_id(id),_originAddress(originAddress),_from(from),_destinationAddress(destinationAddress),_hopTtl(hopTtl),_numOfHops(numOfHops),_data(data),_dataLength(data.size())
//{
//	printPackage();
//}

Package::Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, Data data ,int dataLength, Opcode opcode)
	: _id(id), _originAddress(originAddress), _from(from), _destinationAddress(destinationAddress), _hopTtl(hopTtl), _numOfHops(numOfHops),_data(data),_opcode(opcode)
{
	//for (int i = 0; i < dataLength; ++i) {
	//	_data.push_back(data[i]);
	//}
	//printPackage();
}

Package::Package(int id) :_hopTtl(DEFAULT_HOP_TTL), _numOfHops(0), _id(id)
{
}

Package::Package() : _hopTtl(DEFAULT_HOP_TTL), _numOfHops(0)
{
	_id = 0;
}

const int Package::getId() { return _id; }

const int Package::getOriginAddress() { return _originAddress; }

const int Package::getFrom() { return _from; }

const int Package::getDestinationAddress() { return _destinationAddress; }

const int Package::getHopTtl() { return _hopTtl; }

const int Package::getNumOfHops() { return _numOfHops; }

Data Package::getData() { return _data; }



//const char* Package::getDataAsCharArray() {
//	char* data = new char[_dataLength];
//	for (int i = 0; i < _dataLength; ++i) {
//		data[i] = _data[i];
//	}
//	return data;
//}

int Package::getDataLength() { return _dataLength; }

Opcode Package::getOpcode() { return _opcode; }

void Package::setOriginAddress(int originAddress) { _originAddress = originAddress; }

void Package::setFrom(int from) { _from = from; }

void Package::setDestinationAddress(int destinationAddress) { _destinationAddress = destinationAddress; }

void Package::setHopTtl(int hopTtl) { _hopTtl = hopTtl; }

void Package::setNumOfHops(int numOfHops) { _numOfHops = numOfHops; }

void Package::setData(Data data, int dataLength) {
	_data = data;
	_dataLength = dataLength;
}
void Package::setId(int id)
{
	_id = id;
}
//void Package::setData(char* data) {
//	_data = data;
//	_dataLength = _data.size();
//}

void Package::setOpcode(Opcode opcode) {
	if (validateOpcode(opcode))
		_opcode = opcode;
}

bool Package::validateOpcode(Opcode opcode) {
	//Validate opcode exist
	return true;
}

void Package::printPackage() {
	Serial.println("\nPackage:");
	Serial.print("Package ID : ");
	Serial.println(_id);
	Serial.print("OriginAddress : ");
	Serial.println(_originAddress);
	Serial.print("From : ");
	Serial.println(_from);
	Serial.print("DestinationAddress : ");
	Serial.println(_destinationAddress);
	Serial.print("HopTtl : ");
	Serial.println(_hopTtl);
	Serial.print("NumOfHops : ");
	Serial.println(_numOfHops);
	Serial.print("Data : ");
	//Serial.println(getDataAsCharArray());
}

Package::~Package()
{
}
