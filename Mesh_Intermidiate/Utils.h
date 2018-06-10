//#pragma once
//#include <WString.h>
//
//static void parseString(String str, char delimiter, String* parsedString, int numOfValues) {
//	int index1 = 0;
//	int index2 = 0;
//	int j = 0;
//	Serial.println(str);
//	for (int i = 0; i < str.length(); ++i) {
//		Serial.print(str.charAt(i));
//		if (str.charAt(i) == delimiter) {
//			index2 = i;
//			parsedString[j] = str.substring(index1, index2 -1);
//			index1 = index2 + 1;
//			++j;
//		}
//	}
//	for (int i = 0; i < numOfValues; ++i) {
//		Serial.println(parsedString[i]);
//	}
//}
