#include "Package.h"

//Package::Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, Data* data ,int dataLength, Opcode opcode)
//	: _id(id), _originAddress(originAddress), _from(from), _destinationAddress(destinationAddress), _hopTtl(hopTtl), _numOfHops(numOfHops),_data(data),_opcode(opcode)
//{
//	_propagate = 5;
//}

Package::Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, String data, int dataLength, Opcode opcode)
	: _id(id), _originAddress(originAddress), _from(from), _destinationAddress(destinationAddress), _hopTtl(hopTtl), _numOfHops(numOfHops), _strData(data), _opcode(opcode)
{
	_propagate = 5;
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

int Package::getSendPriority()
{
	return _sendPriority;
}

//Data* Package::getData() { return _data; }
String Package::getData() { return _strData; }
int Package::getPropagation()
{
	return _propagate;
}

int Package::getSendInterval()
{
	return _sendInterval;
}

int Package::getDataLength() { return _dataLength; }

Opcode Package::getOpcode() { return _opcode; }

void Package::setOriginAddress(int originAddress) { _originAddress = originAddress; }

void Package::setFrom(int from) { _from = from; }

void Package::setDestinationAddress(int destinationAddress) { _destinationAddress = destinationAddress; }

void Package::setHopTtl(int hopTtl) { _hopTtl = hopTtl; }

void Package::setNumOfHops(int numOfHops) { _numOfHops = numOfHops; }

//void Package::setData(Data* data, int dataLength) {
//	_data = data;
//	_dataLength = dataLength;
//}
void Package::setData(String data) {
	_strData = data;
	
}
void Package::setId(int id)
{
	_id = id;
}

//void Package::setSendPriority(SEND_INTERVAL priority)
//{
//	switch (priority) {
//	case SEND_INTERVAL_LOW:
//		_sendInterval = SEND_INTERVAL_LOW;
//		break;
//	case SEND_INTERVAL_MEDIUM:
//		_sendInterval = ;
//	case SEND_INTERVAL_HIGH:
//	}
//}

void Package::setOpcode(Opcode opcode) {
	if (validateOpcode(opcode))
		_opcode = opcode;
}

void Package::setSendInterval(int sendInterval)
{
	_sendInterval = sendInterval;
}

void Package::setPropagation(int propagation)
{
	_propagate = propagation;
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
	//_data->printData();
	//////Test!! Don't forget to remove
	//GPSData*gpsData = static_cast<GPSData*>(_data);
	//Serial.print("Longitude : ");
	//Serial.println((*gpsData).getLongitude());
	//Serial.print("Latitude : ");
	//Serial.println((*gpsData).getLatitude());
	//Serial.print("Time : ");
	//Serial.println((*gpsData).getTime());
	//Serial.print("Date : ");
	//Serial.println((*gpsData).getDate());


	//MoveData* moveData = static_cast<MoveData*>(_data);
	//Serial.print("Direction : ");
	//Serial.println((*moveData).getDirection());
	//Serial.print("amount: ");
	//Serial.println((*moveData).getAmount());

}

Package::~Package()
{
}
