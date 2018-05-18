#pragma once
//#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Package.h"
#include "Status.h"
#include "Opcode.h"
#include "GPS.h"
#include "DroneController.h"
#include "Camera.h"
static const int HQ_ID = 0;
class MeshNode
{
	const byte READ_ADDRESS[6] = { 0 };
	const byte WRITE_ADDRESS[6] = { 1 };
	const int _uniqueId;
	const int _channel;
	GPS _gps;
	Camera camera;
	DroneController droneConnector;

	boolean validateValue(int amount);
public:
	MeshNode(int channel);
	//MeshNode(const MeshNode &node);
	//const int getChannel();
	void init();
	bool isDataAvailable();
	Status readData();
	Status processData(Opcode opcode, char* receivedData, size_t dataLength);
	Package createPackage(char* data, int dataSize, Opcode opcode, int destinationAddress);
	Status forwardPackage(Package package);
	Status sendPackage(Package package);
	void printPackage(Package package);
	~MeshNode();
};

