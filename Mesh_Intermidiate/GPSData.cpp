#include "GPSData.h"
GPSData::GPSData()
{
}
size_t GPSData::serialize_size() const {
	return SerializablePOD<double>::serialize_size(_latitude) +
		SerializablePOD<double>::serialize_size(_longitude) +
		SerializablePOD<u32>::serialize_size(_time)+
		SerializablePOD<u32>::serialize_size(_date);
}

void GPSData::serialize(char* dataOut) const
{
	dataOut = SerializablePOD<double>::serialize(dataOut, _latitude);
	dataOut = SerializablePOD<double>::serialize(dataOut, _longitude);
	dataOut = SerializablePOD<u32>::serialize(dataOut, _time);
	dataOut = SerializablePOD<u32>::serialize(dataOut, _date);
}

void GPSData::deserialize(const char* dataIn)
{
	dataIn = SerializablePOD<double>::deserialize(dataIn, _latitude);
	dataIn = SerializablePOD<double>::deserialize(dataIn, _longitude);
	dataIn = SerializablePOD<u32>::deserialize(dataIn, _time);
	dataIn = SerializablePOD<u32>::deserialize(dataIn, _date);
}