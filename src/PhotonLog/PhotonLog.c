#include "PhotonLog.h"

#ifdef PLQueueLogMode
#else
#include <stdio.h>
#endif

void _PLLogNumber(long toChage, int radix) {
	int digit;
	long current = toChage;
	if (current == 0) {
		return;
	} 
	if (current < 0) {
		PLLogChar('-');
		_PLWasMinus = 1;
		current = -current;
	}
	digit = current%radix;
	current = current/radix;
	digit = digit + ((digit >= 10)? 'A'-10 : '0');
	_PLLogNumber(current, radix);
	PLLogChar(digit);	
}

void PLLogNumber(long toChage, int radix) {
	if (toChage == 0) {
		PLLogChar('0');
		return;
	} 
	_PLLogNumber(toChage, radix);	
}

#ifdef PLQueueLogMode

struct PLMessagetType PLMessage[PLMaxMessageSize];

unsigned int PLCurrentIndex = 0;

void _PLLog(void* message, unsigned int parameterCount, unsigned int _1, unsigned int _2, unsigned int _3, unsigned int _4) {
	*(int*)message = (int)&(PLMessage[PLCurrentIndex]);
	PLMessage[PLCurrentIndex].message = message;
	PLMessage[PLCurrentIndex]._1 = _1;
	PLMessage[PLCurrentIndex]._2 = _2;
	PLMessage[PLCurrentIndex]._3 = _3;
	PLMessage[PLCurrentIndex]._4 = _4;
	PLCurrentIndex++;
	if (PLCurrentIndex >= PLMaxMessageSize)  PLCurrentIndex = 0;
}
void PLLogChar(char aChar) {_PLLog((void*) aChar,0,0,0,0);}
void PLLogString(void* aString) { _PLLog(aString, 0,0,0,0);}
void PLLogSetFile(File* file) {}


#else

char* _PLMessage;
char* _PLMessageChar;
char* _PLMessageStr;
unsigned int _PL_1, _PL_2, _PL_3, _PL_4;
unsigned int _PLParameterCount;
unsigned int _PLWasMinus;

#ifdef X86
static FILE* aFile = 0;
void PLLogChar(char aChar) { if(aFile == 0) aFile = stdout; fputc(aChar,aFile);_PLMessageChar = (char*)aChar;}
void PLLogString(char* aString) {if(aFile == 0) aFile = stdout; fprintf(aFile, aString);_PLMessageStr = aString;}
void PLLogSetFile(FILE* file) {aFile = file;}
#endif

#ifdef ARM
#ifndef FILE
#define FILE void
#endif
#ifdef Thumb
 #define SemihostingSWI 0xAB
#else
 #define SemihostingSWI 0x123456
#endif
__swi(SemihostingSWI) void __PLLogChar(unsigned op, const char *c);
void PLLogChar(char aChar) {__PLLogChar(0x3, &aChar);_PLMessageChar = (char*)aChar;}
void PLLogString(char* aString) {__PLLogCharString(0x4, aString);_PLMessageStr = aString;}
void PLLogSetFile(FILE* file){}
#endif
void PLLogHex(long hex) {
	PLLogString("0x");
	PLLogNumber(hex, 16);
}
void PLLogDecimal(long decimal) {
	PLLogNumber(decimal, 10);
}
void __PLLog(char* message, unsigned int parameterCount, unsigned int _1, unsigned int _2, unsigned int _3, unsigned int _4) {
	char* current = message;
	while (*current != 0) {
		if ( *(current+1) == '_' && *(current+2) =='_') {

			switch (*current) {
			case 'd':
				PLLogDecimal(_1);
				__PLLog(current+3, parameterCount-1, _2, _3, _4, 0);
				return;
			case 'h':
				PLLogHex(_1);
				__PLLog(current+3, parameterCount-1, _2, _3, _4, 0);
				return;
			case 's':
				PLLogString((char*)_1);
				__PLLog(current+3, parameterCount-1, _2, _3, _4, 0);
				return;
			}
		}
		PLLogChar(*current++);
	}

}


void _PLLog(char* message, unsigned int parameterCount, unsigned int _1, unsigned int _2, unsigned int _3, unsigned int _4) {
	__PLLog(message, parameterCount, _1, _2, _3, _4);
	_PLMessage = message;
	_PL_1 = _1;
	_PL_2 = _2;
	_PL_3 = _3;
	_PL_4 = _4;
	_PLParameterCount = parameterCount;
}
#endif
