#pragma once
//#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Package.h"
#include "Status.h"
#include "Opcode.h"
#include "GPS.h"
#include <PriorityQueue.h>
#include "MoveData.h"
#include "DroneController.h"
//#include "Camera.h"

#define DEFAULT_PROPAGATION 5
#define MAX_MESSAGES  1000
#define COM 4
int hash(int x);
static const int HQ_ID = 0;
class MeshNode
{


#ifdef COM
#if COM == 4
	//COM 4
	const byte READ_ADDRESS[6] = { 0 };
	const byte WRITE_ADDRESS[6] = { 1 };
#else
	//COM 5
	const byte READ_ADDRESS[6] = { 1 };
	const byte WRITE_ADDRESS[6] = { 0 };
#endif
#endif
	/*const*/ int _uniqueId;
	const int _channel;
	GPS _gps;
	DroneController _droneController;
	int _nextPackageID = 0;
	int* _packageIdArray;
	SimpleTimer _timer;
	int _timerNumber;

	
	bool validateValue(int amount);

public:
	int checkRequestId(int requestId);

	MeshNode(int channel);
	Package createPackage(Data* data, int dataLength, Opcode opcode, int destinationAddress);
	void init();
	bool isDataAvailable();
	Status readData();
	//Status processData(Opcode opcode, Data* receivedData, size_t dataLength);
	Status MeshNode::processData(Opcode opcode, String receivedData, size_t dataLength);
	Status forwardPackage(Package& package);
	static Status sendPackage(Package& package);
	static void updatePackageDetails(Package& package);
	void printPackage(Package package);
	static void propagatePackages();
	bool isInitComplete();
	void runTimers();
	const int getId();
	~MeshNode();
};



