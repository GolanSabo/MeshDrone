#pragma once
#include "vector.h"
#include "Hashtable.h"
#include <SPI.h>
#include "GPSData.h"
#include "MoveData.h"
//#include "Message.h"
const int DEFAULT_HOP_TTL = 5;
enum Status { FAIL, SUCCESS, PROCESSED, DROP, FORWARDED };
enum Opcode { LEFT_REQUEST, RIGHT_REQUEST, UP_REQUEST, DOWN_REQUEST, PIC_REQUEST, PIC_RESPONSE, MOVE, GPS_REQUEST, GPS_RESPONSE };
enum SEND_INTERVAL { SEND_INTERVAL_LOW = 10000, SEND_INTERVAL_MEDIUM = 5000, SEND_INTERVAL_HIGH = 1000 };
class Package
{
	//HEADER

	//The unique ID of the package
	int _id;
	//The address of the creator of the package
	int _originAddress;
	//The address of the sender node
	int _from;
	//The address of the destination node
	int _destinationAddress;
	//Number of hops before discarding the package
	int _hopTtl;
	//Number of hops this package was transferred
	int _numOfHops;

	//MESSAGE
	//Vector<Message> message[];

	//The unique value of the required operation
	Opcode _opcode;
	//How many time to send this package
	int _propagate;
	SEND_INTERVAL _sendPriority;
	int _sendInterval;

	//DATA
	//The data of the package
	//Data* _data;
	String _strData;
	//The size of the data in bytes
	int _dataLength;

	bool validateOpcode(Opcode opcode);
public:
	//Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, Data* data, int dataLength, Opcode opcode);
	Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, String data, int dataLength, Opcode opcode);

	Package(int id);
	Package();
	const int getId();
	const int getOriginAddress();
	const int getFrom();
	const int getDestinationAddress();
	const int getHopTtl();
	const int getNumOfHops();
	int getSendPriority();
	//Data* getData();
	String getData();
	int getPropagation();
	int getSendInterval();
	int getDataLength();
	Opcode getOpcode();
	void setOriginAddress(int originAddress);
	void setFrom(int from);
	void setDestinationAddress(int destinationAddress);
	void setHopTtl(int hopTtl);
	void setNumOfHops(int numOfHops);
	//void setData(Data* data, int dataLength);
	void setData(String data);
	void setId(int id);
	void setOpcode(Opcode opcode);
	void setSendInterval(int sendInterval);
	void setPropagation(int propagation);
	void printPackage();
	
	~Package();

};