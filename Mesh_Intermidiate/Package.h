#pragma once
#include "vector.h"
#include "Hashtable.h"
#include <SPI.h>
static const int DEFAULT_HOP_TTL = 5;
class Package
{
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
	//The data of the package
			//Vector<char*> _data;
	char* _data;
	//The size of the data in bytes
	int _dataLength;
	//The unique value of the required operation
	Opcode _opcode;

	bool validateOpcode(Opcode opcode);
public:
	//Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, Vector<char*> data);
	Package(int id, int originAddress, int from, int destinationAddress, int hopTtl, int numOfHops, char* data, int dataLength, Opcode opcode);
	Package(int id);
	Package();
	const int getId();
	const int getOriginAddress();
	const int getFrom();
	const int getDestinationAddress();
	const int getHopTtl();
	const int getNumOfHops();
	char* getData();
	//const char* getDataAsCharArray();
	const int getDataLength();
	const Opcode getOpcode();
	void setOriginAddress(int originAddress);
	void setFrom(int from);
	void setDestinationAddress(int destinationAddress);
	void setHopTtl(int hopTtl);
	void setNumOfHops(int numOfHops);
	void setData(char* data, int dataLength);
	//void setData(Vector<char*> data);
	void setOpcode(Opcode opcode);
	void printPackage();
	~Package();

};