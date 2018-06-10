#pragma once
//////////////////////CONFIGURATION///////////////////////////////
#define chanel_number 8  //set the number of chanels
#define default_servo_value 1500  //set the default servo value
//#define PPM_FrLen 22500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_FrLen 50000  
#define PPM_PulseLen 1000  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 10  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////


#include <SimpleTimer.h>
static int ppm[chanel_number];
class DroneController
{

public:

	DroneController();
	void move(int direction, int value);

	~DroneController();
	void ppmWrite();
};


