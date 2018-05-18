#include "GPS.h"

//-----------------configuration GPS------------------
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 115200;

GPS::GPS() :_ss(RXPin, TXPin)
{
	_ss.begin(GPSBaud);
}

const GPSData GPS::GetGPSData() {
	GPSData gpsData;
	if (_ss.available() > 0) {
		if (_gps.encode(_ss.read())) {
			gpsData.setLatitude(_gps.location.lat());
			gpsData.setLongitude(_gps.location.lng());
			gpsData.setTime(_gps.time.value());
			gpsData.setDate(_gps.date.value());
			_lastGpsData = gpsData;
		}
	}
	return _lastGpsData;
}


GPS::~GPS()
{
}
