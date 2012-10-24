#include "PhotonLog.h"

#define PTAssert(Expected, Actual) if (Expected != Actual) while(1);
#define PTAssertTrue(Expression) if (!(Expression)) while(1);




#ifdef PLQueueLogMode

PLMessage(intMessage) {PLM;int _1;int _2; int _3;};
void testMessageLogWithoutParameter(void) {
	PLLog(intMessage,1,2);
	PTAssert(1, PLCurrentIndex);
	PTAssert(1, PLMessage[PLCurrentIndex-1]._1);
	PTAssert(2, PLMessage[PLCurrentIndex-1]._2);
	PTAssert(0, PLMessage[PLCurrentIndex-1]._3);
	PTAssert(0, PLMessage[PLCurrentIndex-1]._4);
}

#else

void testMessageLogWithoutParameter(void) {
	PLLog(AB);
	PTAssert(*"A", *_PLMessage);
	PTAssert(*"B", *(_PLMessage+1));
	PTAssert(0, _PL_1);
	PTAssert(0, _PL_1);
	PTAssert(0, _PL_1);
	PTAssert(0, _PL_1);
	PTAssert(0, _PLParameterCount);
}

#endif

void testPutChar(void) {
	PLLogChar('c');
	PTAssert('c', (unsigned int)_PLMessageChar);
}

void testPLLogString(void) {
	char* text = "aString";
	PLLogString(text);
	PTAssert(text, (unsigned int)_PLMessageStr);
}


void testPLLogNumber(void) {
	PLLogNumber(1, 10);
	PTAssert('1', (unsigned int)_PLMessageChar); 
}
void testPLLogNumber_OverDigit(void) {
	PLLogNumber(12, 10);
	PTAssert('2', (unsigned int)_PLMessageChar);
}
void testPLLogNumber_0(void) {
	PLLogNumber(0, 10);
	PTAssert('0', (unsigned int)_PLMessageChar);
}
void testPLLogNumber_Minus(void) {
	_PLWasMinus= 0;
	PLLogNumber(-1, 10);
	PTAssert('1', (unsigned int)_PLMessageChar);
	PTAssertTrue(_PLWasMinus);
}

void testPLLogNumber_MinusOverDigit(void) {
	_PLWasMinus= 0;
	PLLogNumber(-12, 10);
	PTAssert('2', (unsigned int)_PLMessageChar);
	PTAssertTrue(_PLWasMinus);
}
void testPLLogNumber_Hex(void) {
	PLLogNumber(10, 16);
	PTAssert('A', (unsigned int)_PLMessageChar);
}
void testPLLog_d(void) {
	PLLog(d__, 1);
	PTAssert('1', (unsigned int)_PLMessageChar);
}
void testPLLog_h(void) {
	PLLog(h__, 10);
	PTAssert('A', (unsigned int)_PLMessageChar);
}
void testPLLog_s(void) {
	char* Text = "X";
	PLLog(s__, (unsigned int)Text);
	PTAssert(Text, _PLMessageStr);
}
void testPLLog_Embedded(void) {
	PLLog(ad__b, 10);
	PTAssert('b', (unsigned int)_PLMessageChar);
}
void main() {

	testMessageLogWithoutParameter();
	testPutChar();
	testPLLogString();
	testPLLogNumber();
	testPLLogNumber_OverDigit();
	testPLLogNumber_0();
	testPLLogNumber_Minus();
	testPLLogNumber_MinusOverDigit();
	testPLLogNumber_Hex();
	testPLLog_d();
	testPLLog_h();
	testPLLog_s();
	testPLLog_Embedded();
}
