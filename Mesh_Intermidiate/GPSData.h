#pragma once
#include "Serializable.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "Data.h"
class GPSData : public Data
{
	double _latitude;
	double _longitude;
	u32 _time;
	u32 _date;

public:
	GPSData();
	GPSData(double latitude, double longitude, u32 time, u32 date) :_latitude(latitude),_longitude(longitude),_time(time){};
	inline const double getLatitude() { return _latitude; }
	inline const double getLongitude() { return _longitude; }
	inline const u32 getTime() { return _time; }
	inline const u32 getDate() { return _date; }
	inline void setLatitude(double latitude) { _latitude = latitude; }
	inline void setLongitude(double longitude) { _longitude = longitude; }
	inline void setTime(u32 time) { _time = time; }
	inline void setDate(u32 date) { _date = date; }

	//virtual size_t serialize_size() const;
	//virtual void serialize(char* dataOut) const;
	//virtual void deserialize(const char* dataIn);
	~GPSData() {};
};
