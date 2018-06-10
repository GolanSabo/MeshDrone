#include "GPS.h"

//-----------------configuration GPS------------------
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 115200;

GPS::GPS() :_ss(RXPin, TXPin)
{
	_ss.begin(GPSBaud);
}

const Status GPS::GetGPSData(GPSData& gpsData) {
	Status status = FAIL;
	Serial.println("GPS DATA!");
	if (_ss.available() > 0) {
		if (_gps.encode(_ss.read())) {

			gpsData.setLatitude(_gps.location.lat());
			Serial.println((int)gpsData.getLatitude());
			gpsData.setLongitude(_gps.location.lng());
			Serial.println((int)_gps.location.lng());
			gpsData.setTime(_gps.time.value());
			Serial.println((int)_gps.time.value());
			gpsData.setDate(_gps.date.value());
			Serial.println((int)_gps.date.value());
			_lastGpsData = gpsData;
			status = SUCCESS;
			
		}
	}
	return status;
}


GPS::~GPS()
{
}
