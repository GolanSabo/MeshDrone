//#pragma once
//#include <string.h>
//#include <stddef.h>
//template <typename POD>
//class SerializablePOD
//{
//public:
//	static size_t serialize_size(POD str)
//	{
//		return sizeof(POD);
//	}
//	static char* serialize(char* target, POD value)
//	{
//		return memcpy(target, &value, serialize_size(value));
//	}
//	static const char* deserialize(const char* source, POD& target)
//	{
//		memcpy(&target, source, serialize_size(target));
//		return source + serialize_size(target);
//	}
//};
//
//template<>
//size_t SerializablePOD<char*>::serialize_size(char* str)
//{
//	return sizeof(size_t) + strlen(str);
//}
//
//template<>
//const char* SerializablePOD<char*>::deserialize(const char* source, char*& target)
//{
//	size_t length;
//	memcpy(&length, source, sizeof(size_t));
//	memcpy(&target, source + sizeof(size_t), length);
//	return source + sizeof(size_t) + length;
//}
