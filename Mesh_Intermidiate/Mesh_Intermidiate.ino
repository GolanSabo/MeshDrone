#include <SimpleTimer.h>
#include <QueueList_Modified.h>
#include <PriorityQueue.h>
#include <TinyGPS++.h>
#include <stdio.h>
#include <util.h>
#include <Timer1.h>
#include <ThrottleHold.h>
#include <Swashplate.h>
#include <ServoOut.h>
#include <ServoIn.h>
#include <Retracts.h>
#include <rc.h>
#include <PPMOut.h>
#include <PPMIn.h>
#include <PlaneModel.h>
#include <OutputSource.h>
#include <OutputProcessor.h>
#include <output.h>
#include <InputToInputMix.h>
#include <InputSource.h>
#include <InputProcessor.h>
#include <InputOutputPipe.h>
#include <InputModifier.h>
#include <input.h>
#include <Gyro.h>
#include <FlycamOne.h>
#include <Expo.h>
#include <DualRates.h>
#include <DIPin.h>
#include <DAIPin.h>
#include <Curve.h>
#include <Channel.h>
#include <AIPin.h>
#include <SPI.h>
#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>
#include <SoftwareSerial.h>
#include "MeshNode.h"
#include "DroneController.h"

static const int CHANNEL = 115;
MeshNode node(CHANNEL);

//Package package1(1, node.getId(), node.getId(), 4, 0, 5, &data, 5, MOVE);
int opCode = 4;
void setup() {
	Serial.begin(115200);
	node.init();
}
static int counter2 = 0;
void loop() {
	MoveData d(3,1900);
	//GPSData data("133.23,123.44,33333,33334");
	//d.printData();
#ifdef COM
#if COM == 5
	//COM 5

	if (counter2 == 65535) {
		//Serial.println(d.toString());
		Package package1(1, node.getId(), node.getId(), 4, 0, 5, d.toString(), 5, MOVE);
		node.sendPackage(package1);
		counter2 = 0;
	}
	counter2++;
#endif
#endif
	node.runTimers();
	node.processData(MOVE, d.toString(), 0);
	if (node.isDataAvailable()) {
		node.readData();
	}
	delay(100);
}