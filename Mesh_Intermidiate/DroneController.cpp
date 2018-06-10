#include "DroneController.h"
#include "Package.h"

DroneController::DroneController()
{
	//initiallize default ppm values
	for (int i = 0; i<chanel_number; i++) {
		ppm[i] = default_servo_value;
	}
	ppm[0] = 1000;
	pinMode(sigPin, OUTPUT);
	digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)
}

void DroneController::move(int direction, int value)
{
	//Serial.print(String("Direction") + String(direction) + String("Amount") + String(value));
	ppm[direction] = value;
}

DroneController::~DroneController()
{
}

void DroneController::ppmWrite() {  //generate PPM signal
	static unsigned long lastFrLen;
	static unsigned long lastServo;
	static unsigned long lastPulse;
	static boolean PPM_run;
	static boolean pulse;
	static boolean pulseStart = true;
	static byte counter;
	static byte part = true;
	if (micros() - lastFrLen >= PPM_FrLen) {  //start PPM signal after PPM_FrLen has passed
		lastFrLen = micros();
		PPM_run = true;
	}

	if (counter >= chanel_number) {
		PPM_run = false;
		counter = 0;
		pulse = true;  //put out the last pulse
	}

	if (PPM_run) {
		if (part) {  //put out the pulse
			pulse = true;
			part = false;
			lastServo = micros();
		}
		else {  //wait till servo signal time (values from the ppm array) has passed
			if (micros() - lastServo >= ppm[counter]) {
				counter++;  //do the next channel
				part = true;
			}
		}
	}

	if (pulse) {
		if (pulseStart == true) {  //start the pulse
			digitalWrite(sigPin, onState);
			pulseStart = false;
			lastPulse = micros();
		}
		else {  //will wait till PPM_PulseLen has passed and finish the pulse
			if (micros() - lastPulse >= PPM_PulseLen) {
				digitalWrite(sigPin, !onState);
				pulse = false;
				pulseStart = true;
			}
		}
	}
}