#include "DroneController.h"



DroneController::DroneController()
{
	//initiallize default ppm values
	for (int i = 0; i<chanel_number; i++) {
		_ppm[i] = default_servo_value;
	}
	_ppm[0] = 1000;

	pinMode(sigPin, OUTPUT);
	digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)

	cli();
	TCCR1A = 0; // set entire TCCR1 register to 0
	TCCR1B = 0;

	OCR1A = 100;  // compare match register, change this
	TCCR1B |= (1 << WGM12);  // turn on CTC mode
	TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
	TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
	sei();
}

void DroneController::move(Opcode side, int value)
{
	_ppm[side] = value;
}


DroneController::~DroneController()
{
}
