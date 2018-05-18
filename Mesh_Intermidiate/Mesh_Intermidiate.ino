//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//RF24 radio(7, 8); // CE, CSN
//byte address[][6] = { 0 };
//
//struct package {
//	int id = 1;
//	float temprature = 18.4;
//	char text[100] = "empty";
//}; typedef struct package Package;
//Package data;
//
//void setup() {
//	Serial.begin(115200);
//	bool flag = radio.begin();
//
//	if (flag) {
//		delay(2000);
//		Serial.println("RADIO IS OPEN");
//	}
//	else {
//		delay(2000);
//		Serial.println("RADIO IS NOT OPEN");
//	}
//	
//	
//	radio.setChannel(115);
//
//	radio.setPALevel(RF24_PA_MAX);
//	radio.setDataRate(RF24_250KBPS);
//	radio.openReadingPipe(1, address[0]);
//	radio.openWritingPipe(1);//open writing pipe to address pipe 1
//	
//
//	delay(1000);
//}
//void loop() {
//	Serial.println("LOOP");
//	radio.startListening();
//	if (radio.available()) {
//		while (radio.available()) {
//			Serial.println("Recieved Data");
//			radio.read(&data, sizeof(data));
//		}
//		
//		Serial.print("\nPackage:");
//		Serial.println(data.id);
//		Serial.println(data.temprature);
//		Serial.println(data.text);
//		if (data.id % 2 == 0) {
//			radio.stopListening();
//			Serial.println("Forwarding message");
//			data.text[10] = '!';
//			radio.write(&data, sizeof(data));
//			//radio.write()
//		}
//
//	}
//	else {
//		Serial.println("No Data!");
//	}
//	delay(1000);
//}

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
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <RF24_config.h>
#include <RF24.h>
#include <printf.h>
#include <nRF24L01.h>
#include "MeshNode.h"

static const int CHANNEL = 116;
MeshNode node(CHANNEL);
void setup() {
	Serial.begin(115200);
	delay(1000);
	node.init();
}
void loop() {
	Serial.println("LOOP");
	char charArray[] { 'a', 'v', 'w', 'g', 'c' };
		Package package(5, 1, 2, 1, 5, 0, charArray, 5);
		//char* j = "Message #";
		//package.setData(j, sizeof(j));
		//package.setDestinationAddress(1);
		//package.setOriginAddress(1);
		//package.setHopTtl(5);
		//package.setNumOfHops(0);
		//package.setFrom(1);*/
		//package.printPackage();
		node.sendPackage(package);
		delay(1000);
	if (node.isDataAvailable()) {
		node.readData();
	}
	else {
		delay(1000);
	}
}