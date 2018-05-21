#include "MeshNode.h"

static RF24 radio(7, 8);

MeshNode::MeshNode(int channel):_uniqueId(rand() % 65500), _channel(channel)
{
}

void MeshNode::init() {
	Serial.println("Init");
	radio.begin();
	Serial.println(_channel);
	Serial.println(_uniqueId);
	radio.setChannel(_channel);
	Serial.println("After Channel");
	radio.setPALevel(RF24_PA_MAX);
	Serial.println("AfterPALevel");
	radio.setDataRate(RF24_250KBPS);
	Serial.println("After Data Rate");
	radio.openReadingPipe(1, READ_ADDRESS[0]);
	Serial.println("After Open Reading Pipe");
	radio.openWritingPipe(WRITE_ADDRESS);//open writing pipe to address pipe 1
	Serial.println("After open writing pipe");
	radio.startListening();
	_initComplete = true;
}

bool MeshNode::isDataAvailable() {
	return radio.available();
}

bool MeshNode::isInitComplete()
{
	return _initComplete;
}

Status MeshNode::readData() {
	Serial.println("ReadData");
	Package package;
	Status status(FAIL);
	while (radio.available()) {
		radio.read(&package, sizeof(package));
	}
	printPackage(package);
	if (package.getDestinationAddress() == _uniqueId) {
		Serial.println("Processing Data");
		//processData(package.getOpcode(), package.getData(), package.getDataLength);
		

	}
	else {
		//If the package transferred equal or more than the allowed number of hops
		//don't forward the package
		if (package.getHopTtl() <= package.getNumOfHops())
			status = DROP;
		else {
			forwardPackage(package);
			status = FORWARDED;
		}
	}
}

Status MeshNode::processData(Opcode opcode, char* receivedData, size_t dataLength) {
	Status status(FAIL);
	Data sendData;
	GPSData gpsData;
	Package package;
	switch (opcode) {
	case PIC_REQUEST:
	{
		status = PROCESSED;
		break;
	}
	case GPS_REQUEST:
	{
		gpsData = _gps.GetGPSData();
		size_t dataSize = sizeof(gpsData);
		sendData = gpsData;
		
		package = createPackage(sendData, dataSize, GPS_RESPONSE, HQ_ID);
		sendPackage(package);
		status = PROCESSED;
		break;
	}
	default:
	{
		int amount = atoi(receivedData);
		//if (validateValue(amount))
			//droneConnector.move(opcode, amount);
	}
	}
	if (receivedData != NULL)
		delete[] receivedData;

	return status;
}

boolean MeshNode::validateValue(int amount) {
	if (amount >= 1000 && amount <= 2000)
		return true;
	return false;
}

Package MeshNode::createPackage(Data data, int dataLength, Opcode opcode, int destinationAddress) {
	Package package;
	package.setData(data, dataLength);
	package.setOriginAddress(_uniqueId);
	package.setFrom(_uniqueId);
	package.setOpcode(opcode);
	package.setDestinationAddress(destinationAddress);
	return package;
	
}

Status MeshNode::forwardPackage(Package package){
	Serial.println("ForwardPackage");
	int newNumOfHop = package.getNumOfHops() + 1;
	package.setNumOfHops(newNumOfHop);
	package.setFrom(_uniqueId);
	return sendPackage(package);
}

Status MeshNode::sendPackage(Package package) {
	Serial.println("SendPackage");
	Status status(FAIL);
	radio.stopListening();
	if (radio.write(&package, sizeof(package))) {
		status = SUCCESS;
	}
	radio.startListening();
	return status;
}

void MeshNode::printPackage(Package package) {
	Serial.println("\nPackage:");
	Serial.print("Package ID : ");
	Serial.println(package.getId());
	Serial.print("OriginAddress : ");
	Serial.println(package.getOriginAddress());
	Serial.print("From : ");
	Serial.println(package.getFrom());
	Serial.print("DestinationAddress : ");
	Serial.println(package.getDestinationAddress());
	Serial.print("HopTtl : ");
	Serial.println(package.getHopTtl());
	Serial.print("NumOfHops : ");
	Serial.println(package.getNumOfHops());
	Serial.print("Data : ");
	//Serial.println(package.getDataAsCharArray());
}

MeshNode::~MeshNode()
{
}
