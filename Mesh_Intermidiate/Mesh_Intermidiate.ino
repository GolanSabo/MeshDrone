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





static const int CHANNEL = 115;
MeshNode node(CHANNEL);
GPSData data(133.23, 12323.44, 3333333, 3333333);
Package package1(1, 1, 2, 3, 0, 5, data, 5, LEFT_REQUEST);
void setup() {

	//Timers initialization
	cli();//stop interrupts

		  //set timer0 interrupt at 2kHz
	TCCR0A = 0;// set entire TCCR0A register to 0
	TCCR0B = 0;// same for TCCR0B
	TCNT0 = 0;//initialize counter value to 0
			  // set compare match register for 2khz increments
	OCR0A = 255;// = (16*10^6) / (2000*64) - 1 (must be <256)
				// turn on CTC mode
	TCCR0A |= (1 << WGM01);
	// Set CS01 and CS00 bits for 64 prescaler
	TCCR0B |= (1 << CS01) | (1 << CS00);
	// enable timer compare interrupt
	TIMSK0 |= (1 << OCIE0A);
	sei();//allow interrupts



	Serial.begin(115200);
	delay(1000);
	node.init();
}
void loop() {
	Serial.println("LOOP");
	//char charArray[] { 'a', 'v', 'w', 'g', 'c' };
	//Package package1(1, 1, 2, 3, 0, 5, charArray, 5, LEFT_REQUEST);
		//char* j = "Message #";
		//package.setData(j, sizeof(j));
		//package.setDestinationAddress(1);
		//package.setOriginAddress(1);
		//package.setHopTtl(5);
		//package.setNumOfHops(0);
		//package.setFrom(1);*/
		//package.printPackage();
		node.sendPackage(package1);
		delay(1000);
	if (node.isDataAvailable()) {
		node.readData();
	}
	else {
		delay(1000);
	}
}

ISR(TIMER0_COMPA_vect) {  //change the 0 to 1 for timer1 and 2 for timer2
	if (node.isInitComplete()) {
		int id = package1.getId();
		package1.setId(++id);

		node.sendPackage(package1);
	}
}