#pragma once
#include <DIPin.h>
#include <FlycamOne.h>
#include <ServoOut.h>
#include <Timer1.h>
#include <util.h>

#define SERVOS 1

uint8_t  g_pinsOut[SERVOS] = { 2 };            // Output pins
uint16_t g_input[SERVOS];                    // Input buffer for servoOut, microseconds
uint8_t  g_work[SERVOOUT_WORK_SIZE(SERVOS)]; // we need to have a work buffer for the ServoOut class

// ServoOut requires three buffers:
//     Pins buffer containing output pins
//     Input buffer containing input values in microseconds
//     Work buffer of SERVOOUT_WORK_SIZE(SERVOS) elements for internal calculations
// This setup removes any technical limit on the number of servos you want,
// and makes sure the library doesn't use more memory than it really needs,
// since the client code supplies the buffers.
rc::ServoOut g_ServoOut(g_pinsOut, g_input, g_work, SERVOS);

// FlycamOne object
rc::FlycamOne g_cam;

// We use a digital input pin as a switch
rc::DIPin g_switch(3);
class Camera
{
public:
	Camera();
	void takePicture();
	~Camera();
};

