#include "MeshNode.h"
int hash(int x) {
	x = (((x >> 16) ^ x) * 997) % MAX_MESSAGES;
	x = (((x >> 16) ^ x) * 997) % MAX_MESSAGES;
	x = ((x >> 16) ^ x) % MAX_MESSAGES;
	return x;
}

bool comparePackage(Package a, Package b)
{
	return a.getSendInterval() < b.getSendInterval();
}
static RF24 radio(7, 8);
static PriorityQueue<Package> packageQueue(comparePackage);
static bool _initComplete;
static int counter = 0;


//returns the hash if the id not exist or negative value if id exist
int MeshNode::checkRequestId(int requestId)
{
	int hashVal = hash(requestId);
	if (_packageIdArray[hashVal] <= 0) {
		return hashVal;
	}
	return -1;
}

MeshNode::MeshNode(int channel):_uniqueId(rand() % 65500), _channel(channel),_droneController()
{
#ifdef COM
#if COM == 4
	//COM 4
	_uniqueId = 4;
#else
	//COM 5
	_uniqueId = 5;
#endif
#endif
	_packageIdArray = new int[MAX_MESSAGES];
	_initComplete = false;
	
}

void MeshNode::init() {
	radio.begin();

	radio.setChannel(_channel);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.openReadingPipe(1, READ_ADDRESS[0]);
	radio.openWritingPipe(WRITE_ADDRESS);//open writing pipe to address pipe 1
	radio.startListening();
	_initComplete = true;
	_timerNumber = _timer.setInterval(1000, propagatePackages);

}

bool MeshNode::isDataAvailable() {
	return radio.available();
}

bool MeshNode::isInitComplete()
{
	return _initComplete;
}
static int counter1 = 0;
void MeshNode::runTimers()
{
	_droneController.ppmWrite();
	//if (++counter1 == 50) {
	//	_timer.run();
	//}
}

const int MeshNode::getId()
{
	return _uniqueId;
}

Status MeshNode::readData() {
	Serial.println("ReadData");
	Package package;
	Status status = FAIL;
	if (radio.available()) {
		radio.read(&package, sizeof(package));
		//Serial.print("My ID = ");
		//Serial.println(_uniqueId);
		package.printPackage();
		if (package.getDestinationAddress() == _uniqueId) {
			Serial.println("Processing Data");
			status = processData(package.getOpcode(), package.getData(), package.getDataLength());
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
	else {
		Serial.println("radio no availble");
		status = SUCCESS;
	}
	//if (package.getDestinationAddress() == _uniqueId) {
	//	Serial.println("Processing Data");
	//	status = processData(package.getOpcode(), package.getData(), package.getDataLength());
	//}
	//else {
	//	//If the package transferred equal or more than the allowed number of hops
	//	//don't forward the package
	//	if (package.getHopTtl() <= package.getNumOfHops())
	//		status = DROP;
	//	else {
	//		forwardPackage(package);
	//		status = FORWARDED;
	//	}
	//}
	return status;
}

//Status MeshNode::processData(Opcode opcode, Data* receivedData, size_t dataLength) {
Status MeshNode::processData(Opcode opcode, String receivedData, size_t dataLength) {
	Status status(FAIL);
	Data* sendData;
	
	Package package;
	switch (opcode) {
	case MOVE:
	{
		Serial.println("Move requested");
		MoveData moveData(receivedData);
		_droneController.move(moveData.getDirection(), moveData.getAmount());

		status = PROCESSED;
		break;
	}
	case PIC_RESPONSE:
	{
		Serial.println("Picture requested");
		status = PROCESSED;
		break;
	}
	case GPS_RESPONSE:
	{
		GPSData gpsData;
		Serial.println("GPSData requested");
		if ((status = _gps.GetGPSData(gpsData)) != SUCCESS) {
			break;
		}

		size_t dataSize = sizeof(gpsData);
		sendData = &gpsData;
		package.setPropagation(DEFAULT_PROPAGATION);
		package = createPackage(sendData, dataSize, GPS_RESPONSE, HQ_ID);
		sendPackage(package);
		package.printPackage();

		status = PROCESSED;
		break;
	}
	}

	return status;
}

boolean MeshNode::validateValue(int amount) {
	if (amount >= 1000 && amount <= 2000)
		return true;
	return false;
}

Package MeshNode::createPackage(Data* data, int dataLength, Opcode opcode, int destinationAddress) {
	Package package(_nextPackageID++);
	package.setData(data->toString());
	package.setOriginAddress(_uniqueId);
	package.setFrom(_uniqueId);
	package.setOpcode(opcode);
	package.setDestinationAddress(destinationAddress);
	return package;
	
}

Status MeshNode::forwardPackage(Package& package){
	Serial.println("ForwardPackage");
	int newNumOfHop = package.getNumOfHops() + 1;
	package.setNumOfHops(newNumOfHop);
	package.setFrom(_uniqueId);
	if (checkRequestId(package.getId()) >= 0) {
		packageQueue.push(package);
	}
	return sendPackage(package);
}

Status MeshNode::sendPackage(Package& package) {
	Serial.println("SendPackage");
	Status status(FAIL);
	radio.stopListening();
	if (radio.write(&package, sizeof(package))) {
		status = SUCCESS;
	}
	radio.startListening();
	updatePackageDetails(package);
	return status;
}

void MeshNode::updatePackageDetails(Package & package)
{
	int prop = package.getPropagation();
	if (prop > 1) {
		Serial.println("propagation set to ");
		Serial.println(prop);
		package.setPropagation(prop - 1);
		package.setSendInterval(package.getSendPriority());
		packageQueue.push(package);
	}
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

void MeshNode::propagatePackages() {
	Serial.println("propagatePackage");
	++counter;
	bool update = false;
	if (_initComplete) {
		if (!packageQueue.isEmpty()) {

			Package package = packageQueue.peek();
			int queueSize = packageQueue.count();
			Package* list = new Package[queueSize];
			int packagesToSend = 0;
			//send all the packages according to thier send interval
			while ((package.getSendInterval() - (counter * 1000) <= 0)) {
				list[packagesToSend++] = packageQueue.pop();
				if (packageQueue.count() == 0) {
					break;
				}
				package = packageQueue.peek();
			}
			for (int j = 0; j < packagesToSend; ++j) {
				sendPackage(list[j]);
			}
			//update the time of all the packages in the queue

			queueSize = packageQueue.count();
			delete[] list;
			list = new Package[queueSize];
			for (int i = 0; i < queueSize; ++i) {
				list[i] = packageQueue.pop();
			}
			for (int i = 0; i < queueSize; ++i) {
				list[i].setSendInterval(list[i].getSendInterval() - counter * 1000);
				packageQueue.push(list[i]);
			}
			delete[] list;
			counter = 0;
		}
	}
}

MeshNode::~MeshNode()
{
	if (_packageIdArray != NULL)
		delete[] _packageIdArray;
}


