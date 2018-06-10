#pragma once
//this programm will put out a PPM signal by interrupt and will keep PPM a live
/*-----------------references------------------
https://arduinodiy.wordpress.com/2012/02/28/timer-interrupts/ interrupts explain
https://en.wikipedia.org/wiki/Pulse-position_modulation ppm calc explain
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "GPSData.h"
#include "Package.h"

class GPS
{
	SoftwareSerial _ss;
	TinyGPSPlus _gps;
	GPSData _lastGpsData;

public:
	GPS();
	const Status GetGPSData(GPSData& gpsData);
	~GPS();
};

