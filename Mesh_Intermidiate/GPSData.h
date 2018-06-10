#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "Data.h"
#include "Utils.h"


class GPSData : public Data
{
	double _latitude;
	double _longitude;
	u32 _time;
	u32 _date;

public:
	GPSData();
	GPSData(double latitude, double longitude, u32 time, u32 date) :_latitude(latitude), _longitude(longitude), _time(time) { _data = toString(); };
	GPSData(String data){
		parseData(data);
		_data = data;
	}
	inline const double getLatitude() { return _latitude; }
	inline const double getLongitude() { return _longitude; }
	inline const u32 getTime() { return _time; }
	inline const u32 getDate() { return _date; }
	inline void setLatitude(double latitude) { _latitude = latitude; }
	inline void setLongitude(double longitude) { _longitude = longitude; }
	inline void setTime(u32 time) { _time = time; }
	inline void setDate(u32 date) { _date = date; }
	inline String toString() {
		return  String(_longitude, 3) + ',' + String(_latitude, 3) + ',' + String(_time) + ',' + String(_date);
	}

	inline void printData() {
		Serial.print("Longitude : ");
		Serial.println(getLongitude());
		Serial.print("Latitude : ");
		Serial.println(getLatitude());
		Serial.print("Time : ");
		Serial.println(getTime());
		Serial.print("Date : ");
		Serial.println(getDate());
	}

	inline void parseData(String str) {
		String tmp[4] = { "" };
		int j = 0;
		for (int i = 0; i < str.length(); ++i) {
			char c = str.charAt(i);
			if (c != ',')
				tmp[j] += c;
			else {
				++j;
			}
		}
		_latitude = tmp[0].toDouble();
		_longitude = tmp[1].toDouble();
		_time = tmp[2].toInt();
		_date = tmp[3].toInt();
	}
	~GPSData() {};
};
